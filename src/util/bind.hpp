#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "core/assert.hpp"
#include "core/concepts.hpp"
#include "core/function_traits.hpp"
#include "util/conversions.hpp"
#include "util/variant.hpp"

/* Binds a function making it accessible to the engine. */
#define bind_member_function(class_name, func_name) method<&class_name::func_name>::bind(#func_name)

/* Defines a callback function for a signal event. */
#define signal_callback(slot_owner, slot_callback) \
    std::forward_as_tuple(godot::Callable(slot_owner, #slot_callback), slot_owner)

/* Binds a property making it visible through the engine inspector. */
#define bind_property(class_name, prop_name, prop_type)                    \
    ns::node_property<class_name, prop_type, &class_name::get_##prop_name, \
                      &class_name::set_##prop_name>::add(#prop_name)

namespace ns::inline utils {
    /* Used for function binding, checks the amount of arguments the function has, and binds it
     * accordingly.*/
    template <auto Method>
        requires std::is_member_function_pointer_v<decltype(Method)>
    struct method : function_traits<decltype(Method)>
    {
        using traits_t = function_traits<decltype(Method)>;

        constexpr static void bind(std::string_view&& func_name)
        {
            constexpr std::size_t tup_size = std::tuple_size_v<typename traits_t::arg_types>;
            if constexpr (tup_size == 0)
                godot::ClassDB::bind_method(godot::D_METHOD(func_name.data()), Method);
            else
            {
                const typename traits_t::arg_types_nocvref func_args{};
                std::apply(
                    [&](auto&&... args) {
                        godot::ClassDB::bind_method(godot::D_METHOD(func_name.data()), Method,
                                                    args...);
                    },
                    func_args);
            }
        }
    };

    /*Makes a property visible in the godot inspector.*/
    template <GDObjectDerived TNode, VariantCompatible TProperty, auto GetterMethod, auto SetterMethod>
    struct node_property
    {
        using getter_traits = function_traits<decltype(GetterMethod)>;
        using setter_traits = function_traits<decltype(SetterMethod)>;

        constexpr static void add(std::string&& prop_name)
        {
            const std::string getter_name{ "get_" + prop_name };
            const std::string setter_name{ "set_" + prop_name };

            method<GetterMethod>::bind(getter_name);
            method<SetterMethod>::bind(setter_name);

            const godot::PropertyInfo property_info(
                variant_traits<TProperty>::type_info::get_class_info().type,
                godot::String(prop_name.c_str()));

            godot::ClassDB::add_property(TNode::get_class_static(), property_info,
                                         godot::String(setter_name.c_str()),
                                         godot::String(getter_name.c_str()));
        }
    };

    /*Used for defining a function that will be called back when a signal is triggered. Used in
     * conjunction with the Signal struct.*/
    template <auto& Function>
    struct callback_func : function_traits<decltype(Function)>
    {
        using traits_t = function_traits<decltype(Function)>;

        static void bind(std::string_view&& func_name)
        {
            auto class_name = godot::StringName("Main");
            constexpr static std::size_t tup_size = std::tuple_size_v<typename traits_t::arg_types>;
            if constexpr (tup_size == 0)
                godot::ClassDB::bind_static_method(class_name, godot::D_METHOD(func_name.data()),
                                                   Function);
            else
            {
                const typename traits_t::arg_types_nocvref func_args{};
                std::vector<godot::String> vec_strs = detail::to_arg_vec(func_args);
                std::tuple arg_types_str{ detail::arg_vec_to_tuple<tup_size>(vec_strs) };

                std::apply(
                    [&](auto&&... args) {
                        godot::ClassDB::bind_static_method(
                            class_name, godot::D_METHOD(func_name.data()), Function, args...);
                    },
                    func_args);
            }
        }
    };

    /*Creates a signal binding for a node.*/
    template <GDObjectDerived TObject, auto& SignalName>
    class signal_binding
    {
    public:
        using object_t = std::type_identity_t<TObject>;
        using signal_t = std::type_identity_t<signal_binding<object_t, SignalName>>;
        constexpr static std::string_view signal_name{ SignalName };
        static inline std::vector<godot::PropertyInfo> signal_params{};

        // even though we know what TObject is here (the class type adding the signal binding)
        // we can't call TObject::get_class_static() yet since this struct is instantiated before
        // the bindings library initializes the gdextension library, which will just lead to a
        // crash. this will just be set with the class name at runtime when signal_binding::add() is
        // invoked.
        static inline std::string class_name{};

    public:
        /*Adds the signal binding, which can accept arguments for the callback function.*/
        template <typename... TArgs>
        struct add
        {
            using arg_types = std::tuple<std::type_identity_t<TArgs>...>;
            constexpr static size_t arg_count{ std::tuple_size_v<arg_types> };

            add()
            {
                if (class_name.empty())
                    class_name = ns::to<std::string>(object_t::get_class_static());
                else
                {
                    [[maybe_unused]] std::string temp_name = ns::to<std::string>(
                        object_t::get_class_static());
                    runtime_assert(class_name == temp_name);
                }

                if constexpr (arg_count == 0)
                    godot::ClassDB::add_signal(class_name.data(),
                                               godot::MethodInfo(signal_name.data()));
                else
                {
                    arg_types signal_args{};

                    std::apply(
                        [&]<typename... T>(T&&...) {
                            signal_params = { variant_traits<T>::type_info::get_class_info()... };
                        },
                        signal_args);

                    godot::ClassDB::add_signal(
                        class_name.data(),
                        godot::MethodInfo(signal_name.data(),
                                          std::forward<decltype(signal_params)>(signal_params)));
                }

                runtime_assert(signal_params.size() == arg_count);
            }
        };
    };

    /*Define a signal connection.*/
    template <auto& SignalName>
    struct signal
    {
    public:
        constexpr static std::string_view signal_name{ SignalName };

    public:
        template <GDObjectDerived TOwnerObj>
        struct connect
        {
        private:
            static inline TOwnerObj* m_signal_owner{ nullptr };

        public:
            /*Attatches a signal to a binding by node owner of the binding.*/
            explicit connect(TOwnerObj* signal_owner)
            {
                static_assert(std::is_same_v<decltype(signal_owner), decltype(m_signal_owner)>);

                m_signal_owner = signal_owner;
                [[maybe_unused]] const std::string class_name = ns::to<std::string>(
                    m_signal_owner->get_class());
                runtime_assert(m_signal_owner->has_signal(signal_name.data()));
            }

            template <typename TNode>
            auto operator<=>(std::tuple<godot::Callable&&, TNode&&> callback)
            {
                auto&& cb{ std::forward<godot::Callable>(std::get<0>(callback)) };
                auto&& callback_owner{ std::get<1>(callback) };

                if (m_signal_owner == nullptr)
                {
                    error_msg("Attempting to connect a signal to a null object");
                    return godot::Error::ERR_DOES_NOT_EXIST;
                }

                if (!callback_owner->has_method(cb.get_method()))
                {
                    error_msg("Signal connection method missing bindings");
                    return godot::Error::ERR_METHOD_NOT_FOUND;
                }

                // TODO: compare and validate the arg count, raw types, and variant conversions
                //       between the matching signal binding record and the callback being
                //       connected.
                return m_signal_owner->connect(signal_name.data(), cb);
            }
        };
    };
}
