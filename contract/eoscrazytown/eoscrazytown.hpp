/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
// #include <cmath>
// #include <string>

#include "config.hpp"
#include "utils.hpp"
// #include "eosio.token.hpp"
 
#define EOS_SYMBOL S(4, EOS)
#define TOKEN_CONTRACT N(eosio.token)

typedef double real_type;
typedef uint8_t card ;



using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

class eoscrazytown : public eosio::contract {
    public:    
        eoscrazytown(account_name self) :
        contract(self),
        _global(_self, _self),_bagsglobal(_self,_self),
        players(_self, _self),bags(_self,_self){}


    // @abi action
    void init(const checksum256& hash);
    // @abi action
    void clear();     
    // @abi action
    void test();
    // @abi action
    void verify( const checksum256& seed, const checksum256& hash );                        
    // @abi action
    void reveal(const checksum256& seed, const checksum256& hash);

    // @abi action
    void transfer(account_name   from,
                  account_name   to,
                  asset          quantity,
                  string         memo);
    
    void onTransfer(account_name   &from,
                    account_name   &to,
                    asset          &quantity,
                    string         &memo);

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


    // @abi table player
    struct player {
        account_name  account;
        vector<int64_t> vbets ;
        uint64_t     primary_key() const { return account; }
        // EOSLIB_SERIALIZE(player, (account)(vbets)) 
    };
    typedef eosio::multi_index<N(player), player> player_index;
    player_index players;  


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



        // @abi table bag i64
        struct bag {
            uint64_t id;         
            account_name owner;
            uint64_t price;
            string slogan;

            uint64_t primary_key() const { return id; }
            uint64_t next_price() const {
                return price * 1.35;
            }
        };
        typedef eosio::multi_index<N(bag), bag> bag_index;
        bag_index bags;   


    void apply(account_name code, action_name action);
  
private:
    const vector<int64_t> getBets(const string &s, const char &c) ;
    auto getBeton( const vector<int64_t> &v );
    const int64_t getTotalBets(const vector<int64_t> &v);

    auto checkBets( const asset &eos, const string &memo,
                vector<int64_t> &vbets, int64_t &totalBets  );                

    auto getResult( const card &a,  const card &b ) ;
};


void eoscrazytown::apply(account_name code, action_name action) {   
    auto &thiscontract = *this;

    if (action == N(transfer)) {
        if (code == N(eosio.token)) {
            execute_action(&thiscontract, &eoscrazytown::onTransfer);
        }
        return;
    }

    if (code != _self) return;
    switch (action) {
        EOSIO_API(eoscrazytown, (init)(test)(clear)(reveal)(newbag)(setslogan));
    };
}

extern "C" {
    [[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) 
    {
        eoscrazytown p(receiver);
        p.apply(code, action);
        eosio_exit(0);
    }
}