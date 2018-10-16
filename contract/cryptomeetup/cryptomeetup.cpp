/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */

#include "cryptomeetup.hpp"

void cryptomeetup::onTransfer(account_name &from, account_name &to, asset &eos, string &memo){
    if (to != _self) return;
    require_auth(from);

    /*
    eosio_assert(eos.is_valid(), "Invalid token transfer...");
    eosio_assert(eos.symbol == EOS_SYMBOL, "only EOS token is allowed");
    eosio_assert(eos.amount > 0, "must buy a positive amount");
    
    if (memo.substr(0, 3) == "buy") {   

        auto g = _bagsglobal.get();
        eosio_assert( g.st <= now() && now() <= g.ed, "not correct time.");                                                      
        memo.erase(0, 4);
        std::size_t s = memo.find(' ');
        if (s == string::npos)
        {
            s = memo.size();
        }

        auto id = string_to_price(memo.substr(0, s));
        eosio_assert(id <= 100 || now() >= 1539403200 + 8*60*60, "no character exist");
        //  auto id = 0;
        memo.erase(0, s + 1);
        auto itr = bags.find(id);
        eosio_assert(itr != bags.end(), "no character exist");
        eosio_assert(eos.amount >= itr->next_price(), "no enough eos");
        eosio_assert(from != itr->owner, "cannot buy with yourself" );

        asset d(eos.amount - itr->next_price(), EOS_SYMBOL);

        if (d.amount > 0 && _self != from){

        action( // winner winner chicken dinner
            permission_level{_self, N(active)},
            TOKEN_CONTRACT, N(transfer),
            make_tuple(_self, from, d,
                       std::string("refund")))
            .send();
        }

        d.amount = itr->next_price() - itr->price;

        auto ref_b = d;
        ref_b.amount /= 10;


        auto ref = eosio::string_to_name(memo.c_str());
        if (is_account(ref) && ref != from && _self != from)
        {   
            if (ref_b.amount > 0) {
            action( // winner winner chicken dinner
                permission_level{_self, N(active)},
                N(eosio.token), N(transfer),
                make_tuple(_self, ref, ref_b,
                           std::string("ref bonus")))
                .send();
            }
        }
        else
        {
            g.team += ref_b.amount;
        }
        d.amount -= ref_b.amount * 4;

        g.team += ref_b.amount ;
        g.pool += ref_b.amount * 2;
        g.last = from;
        g.ed = now() + 60 * 60 * 24;

        _bagsglobal.set(g, _self);

        auto delta = d;
        delta.amount += itr->price;

    if(delta.amount > 0 &&  _self !=itr->owner){
        action( // winner winner chicken dinner
            permission_level{_self, N(active)},
            N(eosio.token), N(transfer),
            make_tuple(_self, itr->owner, delta,
                       std::string("next hodl")))
            .send();
    }

        bags.modify(itr, 0, [&](auto &t) {
            t.owner = from;
            t.price = itr->next_price();
        });

        return;
    }*/
}