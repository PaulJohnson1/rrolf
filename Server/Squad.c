#include <Server/Squad.h>

#include <string.h>
#include <stdlib.h>

#include <Server/Server.h>

void rr_squad_init(struct rr_squad *this)
{
    memset(this, 0, sizeof *this);
    for (uint32_t i = 0; i < 6; ++i)
        this->squad_code[i] = (char) (97 + rand() % 26);
}

uint8_t rr_squad_has_space(struct rr_squad *this)
{
    return this->member_count < RR_SQUAD_MEMBER_COUNT;
}

void rr_squad_add_client(struct rr_squad *this, struct rr_server_client *client)
{
    if (this->member_count == 0)
        rr_squad_init(this);
    for (uint32_t i = 0; i < RR_SQUAD_MEMBER_COUNT; ++i)
    {
        if (this->members[i].in_use)
            continue;
        memset(&this->members[i], 0, sizeof this->members[i]);
        client->squad_pos = i;
        this->members[i].client = client;
        this->member_count += 1;
        this->members[i].in_use = 1;
        return;
    }
}

void rr_squad_remove_client(struct rr_squad *this, struct rr_server_client *client)
{    
    this->member_count -= 1;
    memset(&this->members[client->squad_pos], 0, sizeof (struct rr_squad_member));
    client->squad_pos = 0;
    if (this->member_count == 0)
        rr_squad_init(this);
}

uint8_t rr_client_find_squad(struct rr_server *this, struct rr_server_client *member)
{
    for (uint8_t i = 0; i < RR_SQUAD_COUNT; ++i)
        if (rr_squad_has_space(&this->squads[i]))
            return i;
    return RR_ERROR_CODE_INVALID_SQUAD;
}

uint8_t rr_client_create_squad(struct rr_server *this, struct rr_server_client *member)
{
    for (uint8_t i = 0; i < RR_SQUAD_COUNT; ++i)
        if (this->squads[i].member_count == 0)
        {
            rr_squad_init(&this->squads[i]);
            this->squads[i].private = 1;
            return i;
        }
    return RR_ERROR_CODE_INVALID_SQUAD;
}

uint8_t rr_client_join_squad_with_code(struct rr_server *this, char *code)
{
    for (uint8_t i = 0; i < RR_SQUAD_COUNT; ++i)
        if (memcmp(this->squads[i].squad_code, code, 6) == 0)
            return rr_squad_has_space(&this->squads[i]) ? i : RR_ERROR_CODE_FULL_SQUAD;
    return RR_ERROR_CODE_INVALID_SQUAD;
}

uint8_t rr_client_join_squad(struct rr_server *this, struct rr_server_client *member, uint8_t pos)
{
    if (!rr_squad_has_space(&this->squads[pos]))
        return 0;
    rr_squad_add_client(&this->squads[pos], member);
    member->squad = pos + 1;
    return 1;
}

void rr_client_leave_squad(struct rr_server *this, struct rr_server_client *member)
{
    if (member->squad == 0)
        return;
    printf("leaving squad %d\n", member->squad - 1);
    rr_squad_remove_client(&this->squads[member->squad - 1], member);
    member->squad = 0;
}

struct rr_squad_member *rr_squad_get_client_slot(struct rr_server *this, struct rr_server_client *member)
{
    if (member->squad == 0)
        return NULL;
    return &this->squads[member->squad - 1].members[member->squad_pos];
}