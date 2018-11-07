/**
 *  @dev minakokojima
 *  @copyleft ／人◕ ‿‿ ◕人＼
 *  Want to make a Contract with me?
 *  I am the linear version of kyubey protocol.
 */

// dacincubator

#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/transaction.hpp>

#include <cmath>

#define EOS_SYMBOL S(4, EOS)

typedef double real_type;

using eosio::asset;
using eosio::symbol_type;
using eosio::action;
using eosio::permission_level;

const uint64_t K = 10000000000;

namespace kyubey {

    /*
    void buy(account_name account, asset in) {    
        asset out;
        _market.modify(_market.begin(), 0, [&](auto &m) {
            out = m.buy(in.amount);
        }); 

        // static char msg[20];
        // sprintf(msg, "delta: %llu", out.amount);
        // eosio_assert(false, msg);
        
        // issue(account, out, "");
        if (out.amount > 0){
            action(
                permission_level{_self, N(active)},
                N(dacincubator), N(transfer),
                make_tuple(_self, account, out, std::string("buy some new token"))
            ).send();    
        }        
    }

    void sell(account_name account, asset in) {            
        //sub_balance(account, in);          
        asset out;
        _market.modify(_market.begin(), 0, [&](auto &m) {
            out = m.sell(in.amount);
        });    
        
        if (out.amount > 0){
            action(
                permission_level{_self, N(active)},
                N(eosio.token), N(transfer),
                make_tuple(_self, account, out, std::string(""))
            ).send();
        }
    }*/

    // @abi table market i64
    struct market {
        uint64_t id = 0;        
        asset supply;
        asset balance;
        uint64_t progress;                         
        uint64_t primary_key() const { return id; }
        
        uint64_t fee(uint64_t x) {
            return x * progress / 10000;
        }

        void update_progress(uint64_t new_progress) {
            eosio_assert(new_progress <= 10000, "out of range");                                
            progress = new_progress;
        }

        asset buy(uint64_t in) {
            // in -= fee(in);
            balance.amount += in;
            uint64_t new_supply = sqrt((real_type)balance.amount * 2 * K) * 100;
            uint64_t delta_supply = new_supply - supply.amount;

            supply.amount = new_supply;
            balance.amount = ((real_type)supply.amount * supply.amount) / 2 / K / 10000;
            return asset(delta_supply, supply.symbol);
        } 

        asset sell(uint64_t in) {
            supply.amount -= in;
            uint64_t new_balance = ((real_type)supply.amount * supply.amount) / 2 / K / 10000;
            uint64_t delta_balance = balance.amount - new_balance;

            balance.amount = new_balance;
            // delta_balance -= fee(delta_balance);
            return asset(delta_balance, balance.symbol);
        }
    };
};
