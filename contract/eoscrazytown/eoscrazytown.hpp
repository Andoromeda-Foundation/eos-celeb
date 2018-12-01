/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
#include <math.h>
const uint64_t K = 10000000000;
// #include <cmath>
// #include <string>

#include "utils.hpp"
#include "council.hpp"
// #include "eosio.token.hpp"
//#include "kyubey.hpp"
 
typedef double real_type;
typedef uint8_t card ;



using std::string;
using eosio::asset;
using eosio::extended_asset;
using eosio::symbol_name;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;

// const uint64_t K = 10000000000;

class eoscrazytown : public council {
    public:    
        eoscrazytown(account_name self) :
        council(self),_bagsglobal(_self,_self),
        players(_self, _self),bags(_self,_self),_CNTmarket(_self, _self) {}


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

   // typedef eosio::multi_index<N(market), kyubey::market> market_index;
   // market_index _market;        

    // @abi action
    void transfer(account_name   from,
                  account_name   to,
                  asset          quantity,
                  string         memo);
    
    void onTransfer(account_name   from,
                    account_name   to,
                    extended_asset quantity,
                    string         memo);

    // @abi action
    void receipt(const rec_reveal& reveal) {
        require_auth(_self);
    }
    // @abi action
    void unstake(account_name from, asset quantity);
    // @abi action
    void claim(account_name from);

    void make_profit(uint128_t amount);


  

        /*
    // @abi table global
    struct global {       
        uint64_t team;
        uint64_t pool;
        uint64_t defer_id;
        
        account_name last;
        time st, ed;
    };

    typedef eosio::multi_index<N(land), land> land_index;
    land_index _land;

    typedef eosio::multi_index<N(market), kyubey::market> market_index;
    market_index _market;    

    typedef singleton<N(global), global> singleton_global;
    singleton_global _global;  */   


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


        // @abi table market i64
        struct market {
            uint64_t id = 0;        
            asset supply; // token
            asset balance;  // eos
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
                in -= fee(in);
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
                delta_balance -= fee(delta_balance);
                return asset(delta_balance, balance.symbol);
            }

            EOSLIB_SERIALIZE(market, (id)(supply)(balance)(progress))
        };

        typedef eosio::multi_index<N(market), market> market_index;
        market_index _CNTmarket; 



    void apply(account_name code, action_name action);
  
private:
    const vector<int64_t> getBets(const string &s, const char &c) ;
    auto getBeton( const vector<int64_t> &v );
    const int64_t getTotalBets(const vector<int64_t> &v);

    auto checkBets( const asset &eos, const string &memo,
                vector<int64_t> &vbets, int64_t &totalBets  ); 

    auto checkBetsNew(const asset &eos, vector<int64_t> &vbets, int64_t &totalBets);

    auto getResult( const card &a,  const card &b ) ;
};


struct st_transfer {
    account_name from;
    account_name to;
    asset        quantity;
    string       memo;
};

void eoscrazytown::apply(account_name code, action_name action) {   
    auto &thiscontract = *this;

    if (action == N(transfer)) {
        auto transfer_data = unpack_action_data<st_transfer>();
        onTransfer(transfer_data.from, transfer_data.to, extended_asset(transfer_data.quantity, code), transfer_data.memo);               
        return;
    }

    if (code != _self) return;
    switch (action) {
        EOSIO_API(eoscrazytown, (init)(test)(clear)(reveal)(newbag)(setslogan)(claim)(unstake));
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