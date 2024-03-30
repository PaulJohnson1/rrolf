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

struct rr_vector
{
    float x;
    float y;
};

void rr_vector_set(struct rr_vector *, float, float);
void rr_vector_add(struct rr_vector *, struct rr_vector *);
void rr_vector_sub(struct rr_vector *, struct rr_vector *);
void rr_vector_scale(struct rr_vector *, float);
int rr_vector_equals(struct rr_vector *, struct rr_vector *);
void rr_vector_normalize(struct rr_vector *);
void rr_vector_set_magnitude(struct rr_vector *, float);
float rr_vector_get_magnitude(struct rr_vector *);
float rr_vector_theta(struct rr_vector *);
void rr_vector_from_polar(struct rr_vector *, float, float);
int rr_vector_magnitude_cmp(struct rr_vector *, float);
