#ifndef MINI_ERROR_H
#define MINI_ERROR_H

// Expected error structure:
// struct {
//     bool is_err;
//     T    ok;
//     E    err;
// }

#define mini_is_err(err) ((err).is_err)

#define mini_is_ok(err) (!mini_is_err(err))

#define mini_try(err)                                                          \
    ({                                                                         \
        if (mini_is_err(err)) {                                                \
            return mini_error(err);                                            \
        }                                                                      \
        mini_ok(err);                                                          \
    })

#endif // MINI_ERROR_H
