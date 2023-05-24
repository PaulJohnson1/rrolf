#pragma once

#include <Shared/Entity.h>

#define RR_DEFINE_PUBLIC_FIELD(COMPONENT_NAME, TYPE, FIELD_NAME)                                                \
    void rr_component_##COMPONENT_NAME##_set_##FIELD_NAME(struct rr_component_##COMPONENT_NAME *this, TYPE ___) \
    {                                                                                                           \
        this->protocol_state |= (this->FIELD_NAME != ___) * state_flags_##FIELD_NAME;                           \
        this->FIELD_NAME = ___;                                                                                 \
    }

#define RR_DECLARE_PUBLIC_FIELD(COMPONENT_NAME, TYPE, FIELD_NAME) \
    RR_SERVER_ONLY(void rr_component_##COMPONENT_NAME##_set_##FIELD_NAME(struct rr_component_##COMPONENT_NAME *, TYPE);)

#define RR_ENCODE_PUBLIC_FIELD(NAME, TYPE) \
    if (state & state_flags_##NAME)        \
        proto_bug_write_##TYPE(encoder, this->NAME, "field " #NAME);

#define RR_DECODE_PUBLIC_FIELD(NAME, TYPE) \
    if (state & state_flags_##NAME)        \
        this->NAME = proto_bug_read_##TYPE(encoder, "field " #NAME);
