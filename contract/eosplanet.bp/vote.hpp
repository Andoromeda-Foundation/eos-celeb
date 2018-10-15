/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
 
#define TOKEN_CONTRACT N(dacincubator)
#define TOKEN_SYMBOL S(4, PLT)

typedef double real_type;
typedef uint8_t card ;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

class eosplanet : public eosio::contract {
    public: eosplanet(account_name self) :
        contract(self),
        _voters(_self, _self),
        _proxy(_self, _self),
        _council(_self, _self);

    // @abi table voter_table
    struct voter_info {
        account_name owner = 0; /// the voter
        account_name proxy = 0; /// the proxy set by the voter, if any
        account_name council;   /// the producers approved by this voter if no proxy set
        uint64_t     staked = 0;
        time         last_vote_time = 0; 

        uint64_t primary_key()const { return owner; }
    };       

    // @abi table proxy_table
    struct proxy_info {
        account_name owner = 0; /// the voter
        account_name council; /// the producers approved by this voter if no proxy set
        uint64_t     staked = 0;
        uint64_t     delegated_staked = 0;
        time         last_vote_time = 0; 

        uint64_t primary_key()const { return owner; }
    };

    // @abi table council_table
    struct council_info {
        account_name owner = 0; /// the voter
        account_name council; /// the producers approved by this voter if no proxy set
        uint64_t     total_votes = 0;
        uint64_t     unpaid = 0;

        uint64_t primary_key()const { return owner; }
    };                    
};