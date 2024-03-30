// Copyright (C) 2024  Paul Johnson

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Shared/Entity.h>

#define RR_DEFINE_PUBLIC_FIELD(COMPONENT_NAME, TYPE, FIELD_NAME)               \
    void rr_component_##COMPONENT_NAME##_set_##FIELD_NAME(                     \
        struct rr_component_##COMPONENT_NAME *this, TYPE ___)                  \
    {                                                                          \
        this->protocol_state |=                                                \
            (this->FIELD_NAME != ___) * state_flags_##FIELD_NAME;              \
        this->FIELD_NAME = ___;                                                \
    }

#define RR_DECLARE_PUBLIC_FIELD(COMPONENT_NAME, TYPE, FIELD_NAME)              \
    RR_SERVER_ONLY(void rr_component_##COMPONENT_NAME##_set_##FIELD_NAME(      \
                       struct rr_component_##COMPONENT_NAME *, TYPE);)

#define RR_ENCODE_PUBLIC_FIELD(NAME, TYPE)                                     \
    if (state & state_flags_##NAME)                                            \
        proto_bug_write_##TYPE(encoder, this->NAME, "field " #NAME);

#define RR_DECODE_PUBLIC_FIELD(NAME, TYPE)                                     \
    if (state & state_flags_##NAME)                                            \
        this->NAME = proto_bug_read_##TYPE(encoder, "field " #NAME);
