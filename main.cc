#include <node_api.h>
#include <assert.h>

// typedef enum {
//   napi_ok,
//   napi_invalid_arg,
//   napi_object_expected,
//   napi_string_expected,
//   napi_name_expected,
//   napi_function_expected,
//   napi_number_expected,
//   napi_boolean_expected,
//   napi_array_expected,
//   napi_generic_failure,
//   napi_pending_exception,
//   napi_cancelled,
//   napi_escape_called_twice,
//   napi_handle_scope_mismatch,
//   napi_callback_scope_mismatch,
//   napi_queue_full,
//   napi_closing,
//   napi_bigint_expected,
// } napi_status;

//napi_env is used to represent a context that the underlying N-API implementation can use to persist VM-specific state. 
//This structure is passed to native functions when they're invoked, and it must be passed back when making N-API calls. 
//Specifically, the same napi_env that was passed in when the initial native function was called must be passed to any subsequent nested N-API calls. Caching the napi_env for the purpose of general reuse is not allowed.

//napi_value This is an opaque pointer that is used to represent a JavaScript value.

napi_value Decimal102(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);

  if (argc < 1) {
    napi_throw_type_error(env, nullptr, "must have an argument");
    return nullptr;
  }

  napi_valuetype value_type;
  status = napi_typeof(env, args[0], &value_type);
  assert(status == napi_ok);

  if (value_type != napi_number && value_type != napi_string) {
    napi_throw_type_error(env, nullptr, "argument must be a number of a string");
    return nullptr;
  }

  double value = 0;
  int64_t temp;

  if (value_type == napi_string){
    napi_value num;
    status = napi_coerce_to_number(env, args[0], &num);
    args[0] = num;
  }

  status = napi_get_value_double(env, args[0], &value);
  assert(status == napi_ok);
  temp = int64_t(value * 100);
  if (temp >= 10000000000 || temp <= -10000000000){
    value = 0;
  }
  else {
    value = double(temp)/100;
  }

  status = napi_create_double(env, value, &result);
  assert(status == napi_ok);
  return result;
}

#define DECLARE_NAPI_METHOD(name, func) \
 { name, 0, func, 0, 0, 0, napi_default, 0 }


napi_value Init(napi_env env, napi_value exports) {

  // napi_status napi_define_properties(napi_env env,
  //                                    napi_value object,
  //                                    size_t property_count,
  //                                    const napi_property_descriptor* properties);
  // [in] env: The environment that the N-API call is invoked under.
  // [in] object: The object from which to retrieve the properties.
  // [in] property_count: The number of elements in the properties array.
  // [in] properties: The array of property descriptors.

  // napi_status status;
  // napi_property_descriptor result = DECLARE_NAPI_METHOD("decimal", Decimal102)
  // status = napi_define_properties(env, exports, 1, &result);
  // assert(status == napi_ok);
  // return exports;

  // napi_status napi_create_function(napi_env env,
  //                                  const char* utf8name,
  //                                  size_t length,
  //                                  napi_callback cb,
  //                                  void* data,
  //                                  napi_value* result);
  // [in] env: The environment that the API is invoked under.
  // [in] utf8Name: The name of the function encoded as UTF8. This is visible within JavaScript as the new function object's name property.
  // [in] length: The length of the utf8name in bytes, or NAPI_AUTO_LENGTH if it is null-terminated.
  // [in] cb: The native function which should be called when this function object is invoked.
  // [in] data: User-provided data context. This will be passed back into the function when invoked later.
  // [out] result: napi_value representing the JavaScript function object for the newly created function.
  napi_status status = napi_create_function(env, NULL, 0, Decimal102, nullptr, &exports);
  assert(status == napi_ok);
  return exports;
} 

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)