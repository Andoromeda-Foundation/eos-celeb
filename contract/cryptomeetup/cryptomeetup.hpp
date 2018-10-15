/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>

#include "council.hpp"
#include "NFT.hpp"
// #include <cmath>
// #include <string>

#include "config.hpp"
#include "utils.hpp"
// #include "eosio.token.hpp"
 
typedef double real_type;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

class cryptomeetup : public council {
    public: cryptomeetup(account_name self) :
        council(self),
        _land(_self, _self),
        _player(_self, _self){}

    // @abi action
    void init();
    // @abi action
    void clear();     
    // @abi action
    void test();

    // @abi action
    void transfer(account_name   from,
                  account_name   to,
                  asset          quantity,
                  string         memo);
    
    void onTransfer(account_name   &from,
                    account_name   &to,
                    asset          &quantity,
                    string         &memo);

    void apply(account_name code, action_name action);

    // @abi table bag i64
    struct land : public NFT::tradeable_token {
        uint64_t parent;
        void tax() {
        }
        uint64_t next_price() const {
            return price * 1.35;
        }
    };
    
    // @abi table player
    struct player {
        account_name  account;
        uint64_t land_profit;
        uint64_t ref_profit;
        uint64_t fee_profit;
        uint64_t pool_profit;
        uint64_t staked_income;
        uint64_t council_income;

        uint64_t primary_key() const {return account;}        
        void withdraw() {
        }
    };
        
    typedef eosio::multi_index<N(land), land> land_index;
    land_index _land;   

    typedef eosio::multi_index<N(player), player> player_index;
    player_index _player;  
    
    /*
    // @abi action
    void receipt(const rec_reveal& reveal) {
        require_auth(_self);
    }

    // @abi table global
    struct st_global {       
        uint64_t defer_id = 0;
        checksum256 hash;
        uint8_t dragon ;
        uint8_t tiger ;
        EOSLIB_SERIALIZE( st_global, (defer_id)(hash)(dragon)(tiger)) ;
    };
    typedef singleton<N(global), st_global> singleton_global;
    singleton_global _global;        

    // @abi table bagsglobal
    struct bagsglobal {      
        uint64_t team;
        uint64_t pool;
        account_name last;
        time st, ed;
    };
    typedef singleton<N(bagsglobal), bagsglobal> singleton_bagsglobal;
    singleton_bagsglobal _bagsglobal;   





    uint64_t get_next_defer_id() {
    auto g = _global.get();    
    g.defer_id += 1;
    _global.set(g,_self);
        return g.defer_id;
    }

    template <typename... Args>
    void send_defer_action(Args&&... args) {
        transaction trx;
        trx.actions.emplace_back(std::forward<Args>(args)...);
        trx.send(get_next_defer_id(), _self, false);
    }

  // @abi action
  void newbag(account_name &from, asset &eos);

  // @abi action
  void setslogan(account_name &from, uint64_t id,string memo);
  
private:
    const vector<int64_t> getBets(const string &s, const char &c) ;
    auto getBeton( const vector<int64_t> &v );
    const int64_t getTotalBets(const vector<int64_t> &v);

    auto checkBets( const asset &eos, const string &memo,
                vector<int64_t> &vbets, int64_t &totalBets  );                

    auto getResult( const card &a,  const card &b ) ;
    */
};

void cryptomeetup::apply(account_name code, action_name action) {   
    auto &thiscontract = *this;

    if (action == N(transfer)) {
        if (code == N(eosio.token)) {
            execute_action(&thiscontract, &cryptomeetup::onTransfer);
        }
        return;
    }

    if (code != _self) return;
    switch (action) {
        EOSIO_API(cryptomeetup, (init));
    };
}

extern "C" {
    [[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) 
    {
        cryptomeetup p(receiver);
        p.apply(code, action);
        eosio_exit(0);
    }
}