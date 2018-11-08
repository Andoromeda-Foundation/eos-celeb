/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
#include "config.hpp"
static constexpr time refund_delay = 3*24*3600;

typedef double real_type;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::singleton;
using eosio::permission_level;
using eosio::action;

// TODO
// 还没有办法让council, proxy退出。
// 还没实现72小时后取token。


class council : public eosio::contract {
    public: council(account_name self) :
        contract(self),_global(_self,_self){}

    // @abi table voters
    struct voter_info {
        account_name to = 0;
        uint64_t staked = 0;
        uint64_t payout = 0;
    };       

    // @abi table proxies
    struct proxy_info {
        account_name to = 0;
        uint64_t delegated_staked = 0;
    };

    // @abi table council
    struct council_info {
        uint64_t     total_votes = 0;
        uint64_t     claimed     = 0;          // 已领取的分红
    };          

    typedef singleton<N(voters),  voter_info>  singleton_voters;
    typedef singleton<N(proxies), proxy_info>  singleton_proxies;
    typedef singleton<N(council), council_info>  singleton_council;   
//    singleton_voters _voters;
  //  singleton_proxies _proxies;
   // singleton_council _council;

    
    void stake(account_name from, uint64_t delta) {
        require_auth(from);
        eosio_assert(delta > 0, "must stake a positive amount");
        singleton_voters _voters(_self, from);
        auto v = _voters.get_or_create(_self, voter_info{});
        auto g = _global.get();
        v.staked += delta;
        v.payout += g.earnings_per_share * delta / MAGNITUDE;
        _voters.set(v, _self);
    }
    
    void unstake(account_name from, uint64_t delta) {
        require_auth(from);
        singleton_voters _voters(_self, from);
        auto v = _voters.get_or_create(_self, voter_info{});
        auto g = _global.get();        
        eosio_assert(delta <= v.staked, "don't have enough CMU for unstake");
        // TODO(minakokojima): unvote(v);

        action( // winner winner chicken dinner
            permission_level{_self, N(active)},
            N(dacincubator), N(transfer),
            make_tuple(_self, from, asset(delta, TOKEN_SYMBOL),
                std::string("transfer token by unstake"))
        ).send();


      
        if (g.earnings_per_share * delta / MAGNITUDE <= v.payout) {
            v.payout -= g.earnings_per_share * delta / MAGNITUDE;
        } else {
            v.payout = 0;
        }        

        v.staked -= delta;

        _voters.set(v, _self);
    }    

    // @abi table global
    struct st_global {       
        uint64_t defer_id = 0;
        checksum256 hash;
        uint8_t dragon ;
        uint8_t tiger ;
        uint64_t total_staked;
        uint128_t earnings_per_share;
    };
    typedef singleton<N(global), st_global> singleton_global;
    singleton_global _global;    

    /*
    void unvote(voters_table::const_iterator itr) {
    
        auto p = _proxies.find(itr->to);
        if (p != _proxies.end()) { 
            _proxies.modify(p, 0, [&](auto &pp) {
                pp.delegated_staked -= itr->staked;
            });
            auto c = _council.find(p->to);
            if (c != _council.end()) {                 
                _council.modify(c, 0, [&](auto &cc) {
                    cc.total_votes -= itr->staked;
                });     
            }
            return;
        }        
        auto c = _council.find(itr->to);
        if (c != _council.end()) {             
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes -= itr->staked;
            });
        }
        _voters.modify(itr, 0, [&](auto &v) {

        });
    }*/

     /*
    void unvote(proxies_table::const_iterator itr) {
   
        auto c = _council.find(itr->to);
        if (c != _council.end()) { 
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes -= itr->delegated_staked;
            });
        }
        
    }*/

    void unvote(account_name from) {
        /*
        require_auth(from);        
        auto v = _voters.find(from);
        if (v != _voters.end()) {
            unvote(v);
            return;
        }
        auto p = _proxies.find(from);
        if (p != _proxies.end()) {
            unvote(p);     
            return;
        }*/
    }
     /*
    void vote( voters::const_iterator itr) {
   
        unvote(itr);
        auto p = _proxies.find(itr->to);
        if (p != _proxies.end()) {             
            _proxies.modify(p, 0, [&](auto &pp) {
                pp.delegated_staked += itr->staked;
            });
            auto c = _council.find(p->to);
            if (c != _council.end()) { 
                _council.modify(c, 0, [&](auto &cc) {
                    cc.total_votes += itr->staked;
                });            
            }
            return;
        }        
        auto c = _council.find(itr->to);
        if (c != _council.end()) {             
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes += itr->staked;
            });
            return;          
        }
    }*/
  /* 
    void vote(proxies_table::const_iterator itr) {  
      
        unvote(itr);     
        auto c = _council.find(itr->to);
        if (c != _council.end()) { 
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes += itr->delegated_staked;
            });
        }
    }    
    */
        /*   
    void vote(account_name from, account_name to) {   
  
        require_auth(from);
        auto v = _voters.find(from);
        if (v != _voters.end()) {                   
            _voters.modify(v, 0, [&](auto &vv) {
                vv.to = to;
            });    
            vote(v);
            return;
        }

        auto p = _proxies.find(from);
        if (p != _proxies.end()) {
            _voters.modify(v, 0, [&](auto &vv) {
                vv.to = to;
            });    
            vote(v);
            return;
        }
    }*/

    // 申明自己参与代理
    void runproxy(account_name from) {
        /*
        require_auth(from);

        // warning!!!
        // 申明成为代理需要哪些条件？
        // warning!!!

        auto itr_proxy = _proxies.find(from);
        eosio_assert(itr_proxy != _proxies.end(), "already be proxy");
        _proxies.emplace(_self, [&](auto &p) {
            p.owner = from;
        });

        // warning!!!
        // 打出event, 让前端知道
        // warning!!!
    }    

    // 申明自己参与委员会
    void runcouncil(account_name from) {
        require_auth(from);

        // warning!!!
        // 申明成为委员会需要哪些条件？
        // warning!!!
        
        auto itr_council = _council.find(from);
        eosio_assert(itr_council != _council.end(), "already be council");
        _council.emplace(_self, [&](auto &c) {
            c.owner = from;
        });


        // warning!!!
        // 打出event, 让前端知道
        // warning!!!
        */
    }

    // unstake 72小时后可以取回token
    void getToken(account_name from) {
        /*
        require_auth(from);        
        auto itr = _voters.find(from);
        eosio_assert(itr == _voters.end(), "this account didn't stake");        
        */
   }
};