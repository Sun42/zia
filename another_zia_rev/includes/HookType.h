/// \file

#ifndef HOOKTYPE_H_
# define HOOKTYPE_H_

enum	HookType
  {
    NEW_CONNECTION,
    INPUT_DECODER,
    BODY_DECODER,
    BODY_PROCESSING,
    BODY_ENCODER,
    OUTPUT_ENCODER,
    CLOSED_CONNECTION
  };

#endif
