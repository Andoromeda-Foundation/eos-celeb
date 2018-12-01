#include "eoscrazytown.hpp"

#include <eosiolib/crypto.h>

// @abi action
void eoscrazytown::init(const checksum256 &hash) {
    require_auth(_self);

    auto g = _global.get_or_create( _self, st_global{.hash = hash});    
    g.hash = hash;
    _global.set(g, _self); 
}
// @abi action
void eoscrazytown::clear()
{
    require_auth(_self);

    //_global.remove();

    _bagsglobal.remove();

    // multi_index can't erase when the format changed

    /*
        auto it = db_lowerbound_i64(_self, _self, N(global), 0);
        while (it >= 0) {
            auto del = it;
            uint64_t dummy;
            it = db_next_i64(it, &dummy);
            db_remove_i64(del);
}*/

    //while (players.begin() != players.end()) {
    //    players.erase(players.begin());
    // }



}
// @abi action
void eoscrazytown::test() {
}

void eoscrazytown::make_profit(uint128_t amount) {
    auto g = _global.get();
    g.earnings_per_share += MAGNITUDE * amount / g.total_staked;
    _global.set(g, _self);
}

void eoscrazytown::claim(account_name from) {
    require_auth(from);

    singleton_voters _voters(_self, from);
    auto v = _voters.get_or_create(_self, voter_info{});
    auto g = _global.get();        
    // TODO(minakokojima): unvote(v);
    uint64_t delta = 0;
    if (g.earnings_per_share * v.staked / MAGNITUDE <= v.payout) {
        delta = 0;
    } else {
        delta = g.earnings_per_share * v.staked / MAGNITUDE - v.payout;
    }
    v.payout = g.earnings_per_share * v.staked / MAGNITUDE;
    _voters.set(v, _self);    
    
    //singleton_players _players(_self, from);
    //auto p = _players.get_or_create(_self, player_info{});

    if (delta > 0) {
        send_defer_action(
            permission_level{_self, N(active)},
            N(eosio.token), N(transfer),
            make_tuple(_self, from, 
                asset(delta, EOS_SYMBOL),
                string("claim dividend.")
            )
        );
    }

    // p.pool_profit = 0;
    // _players.set(p, _self);   
}

void eoscrazytown::unstake(account_name from, asset quantity) {
    require_auth(from);
    claim(from);
    council::unstake(from, quantity.amount);
    auto g = _global.get();
    g.total_staked -= quantity.amount;
    _global.set(g, _self);      
}

void eoscrazytown::newbag(account_name &from, asset &eos)
{

    require_auth(_self);
    for (int i=0;i<10;++i){
    bags.emplace(from, [&](auto &p) {
        p.id = bags.available_primary_key();
        p.owner = from;
        p.price = eos.amount;
    });
    }
}

void eoscrazytown::setslogan(account_name &from, uint64_t id, string memo)
{
    auto itr = bags.find(id);
    eosio_assert(itr != bags.end(), "no character exist");
    eosio_assert(memo.size() <= 64, "too long");
    eosio_assert(from == itr->owner, "not the owner.");
    bags.modify(itr, from, [&](auto &t) {
        t.slogan = memo;
    });
}

auto eoscrazytown::checkBets(const asset &eos, const string &memo,
                             vector<int64_t> &vbets, int64_t &totalBets)
{ // check eos.amount == total bets
    vbets = getBets(memo, ',');
    totalBets = getTotalBets(vbets);
    return eos.amount == totalBets;
}

auto eoscrazytown::checkBets(const asset &eos, vector<int64_t> &vbets, int64_t &totalBets)
    totalBets = getTotalBets(vbets);
    return eos.amount == totalBets;
}

// input
/*
void eoscrazytown::onTransfer(account_name &from, account_name &to, asset &eos, string &memo) {        
    if (to != _self) return ;

    require_auth(from);
    eosio_assert(eos.is_valid(), "Invalid token transfer...");
    eosio_assert(eos.symbol == EOS_SYMBOL, "only EOS token is allowed");
    eosio_assert(eos.amount > 0, "must bet a positive amount");
    eosio_assert(memo != "" , "must have bets in memo") ;
    eosio_assert(memo.size() >= 21  , "bets wrong...") ;

                
    // todo: input check non-num
    vector<int64_t> vbets ;
    int64_t totalBets = 0 ;
    eosio_assert( eoscrazytown::checkBets( eos, memo, vbets, totalBets ), "Bets not equal to amount.");
    eosio_assert( totalBets >= 1, "Bets should >= 1=");
    eosio_assert( totalBets <= 100, "Bets should not > 100");

    const auto& sym = eosio::symbol_type(EOS_SYMBOL).name();
    accounts eos_account(N(eosio.token), _self);
    auto old_balance = eos_account.get(sym).balance;

    eosio_assert( totalBets <= old_balance.amount / 2, "Bets too big");
    auto itr = players.find(from);
    if (itr == players.end()) {
        players.emplace(_self, [&](auto& p) {
            p.account = from;
            p.vbets = vbets ;
        });
    } else {
        eosio_assert( false, "Already bet.");
        return ;
    }
}*/

// input
/*
void eoscrazytown::onTransfer(account_name from, account_name to, extended_asset quantity, string memo)
{
    if (to != _self) return;
    require_auth(from);
    //    eosio_assert(memo != "" , "must have something in memo") ;
    //    eosio_assert(memo.size() >= 21  , "bets wrong...") ;

    eosio_assert(quantity.is_valid(), "Invalid token transfer");
    eosio_assert(quantity.amount > 0, "must buy a positive amount");
    auto params = split(memo, ' ');
    eosio_assert(params.size() >= 1, "error memo");    
    
    if (params[0] == "stake") {        
        eosio_assert(quantity.contract == N(dacincubator), "must use true CTN to stake");
        eosio_assert(quantity.symbol == CTN_SYMBOL, "must use CTN to stake");
        stake(from, quantity.amount);
        auto g = _global.get();
        g.total_staked += quantity.amount;
        _global.set(g, _self);     
        return;
    }    

    if (params[0] == "make_profit") {
        eosio_assert(quantity.contract == N(eosio.token), "must use true EOS to make profit");
        eosio_assert(quantity.symbol == EOS_SYMBOL, "must use EOS to make profit");
        make_profit(quantity.amount);
        return;
    }

}
*/
void eoscrazytown::onTransfer(account_name from, account_name to, extended_asset quantity, string memo)
{
    if (to != _self) return;
    if (quantity.contract != N(eosio.token)) return;

    require_auth(from);

    eosio_assert(quantity.is_valid(), "Invalid token transfer");
    eosio_assert(quantity.amount > 0, "must buy a positive amount");
    eosio_assert(quantity.symbol == EOS_SYMBOL, "only EOS token is allowed");

    vector<int64_t> vbets ;
    int64_t totalBets = 0 ;

    auto params = split(memo, ',');
    eosio_assert(params.size() >= 11 , "memo should >= 11");

    vector<uint64_t> bets;
    for (int i=0;i<11;++i) {
        bets.push_back((int64_t)string_to_price( params[i]) );
    }

    // change format
    vector<int64_t> vbets(bets);
    vbets[0] = bets[1];  // (1)
    vbets[1] = bets[6];  // (2)
    vbets[2] = bets[0];  // (3)
    vbets[3] = bets[4];  // (4)
    vbets[4] = bets[9];  // (5)
    vbets[5] = bets[5];  // (6)
    vbets[6] = bets[10]; // (7)
    vbets[7] = bets[2];  // (8)
    vbets[8] = bets[3];  // (9)
    vbets[9] = bets[7];  // (10)
    vbets[10] = bets[8]; // (11)

    eosio_assert( eoscrazytown::checkBets( quantity, vbets, totalBets ), "Bets not equal to amount.");
    eosio_assert( totalBets >= 1000, "Bets should not < 0.1");
    eosio_assert( totalBets <= 200000, "Bets should not > 20");

    
    if(params.size() > 12 && params[12] == PROXY_STRING) {
        auto _amountToProxy = totalBets * 2 / 1000;

        send_defer_action(
            permission_level{_self, N(active)},
            N(eosio.token), N(transfer),
            make_tuple(_self, PROXY, asset(_amountToProxy, EOS_SYMBOL),
                    string("for proxy"))
        );         
    }

    if (memo.size() >= 89 && params.size() > 11) {
        auto refer = eosio::string_to_name(params[11]);
        if( is_account( refer ) && refer != from ) {
            auto _amountToRefer = totalBets * 5 / 1000;
            send_defer_action(
                permission_level{_self, N(active)},
                N(eosio.token), N(transfer),
                make_tuple(_self, refer, asset(_amountToRefer, EOS_SYMBOL),
                        string("for refer"))
            );        
        };
    }
    

    const auto& sym = eosio::symbol_type(EOS_SYMBOL).name();
    accounts eos_account(N(eosio.token), _self);
    auto old_balance = eos_account.get(sym).balance;

    auto itr = players.find(from);
    if (itr == players.end()) {
        players.emplace(_self, [&](auto& p) {
            p.account = from;
            p.vbets = vbets ;
        });
    } else {
        players.modify(itr, from, [&](auto& p) {
            auto totalBets = 0;
            for (int i=0;i<vbets.size();++i) {
                p.vbets[i] += vbets[i];
                totalBets += p.vbets[i];
            }
            eosio_assert( totalBets >= 1000, "Bets should not < 0.1");
            eosio_assert( totalBets <= 200000, "Bets should not > 20");
        });        
    }
}

auto eoscrazytown::getResult(const card &a, const card &b)
{
    string result = "XXXXXXXXXXX";
    const char o = 'O';
    auto aS = a / 13;
    auto bS = b / 13;
    auto aP = a % 13;
    auto bP = b % 13;
    aP ++;
    bP ++;

    if (aP > bP)
        result[0] = o; // (1)
    else if (aP < bP)
        result[1] = o; // (2)
    else
        result[2] = o; // (3)

    if (aS == 1 || aS == 2)
        result[3] = o; // (4) red
    else
        result[5] = o; // (6)

    if (bS == 1 || bS == 2)
        result[4] = o; // (5) red
    else
        result[6] = o; // (7)

    if ((aP & 1) == 1)
        result[7] = o; // (8) odd
    else
        result[8] = o; // (9)

    if ((bP & 1) == 1)
        result[9] = o; // (10) odd
    else
        result[10] = o; // (11)

    return result;
}

const vector<int64_t> eoscrazytown::getBets(const string &s, const char &c)
{ // need protect
    vector<int64_t> vbets;
    auto vs = explode(s, c);
    for (auto n : vs)
    {
        vbets.push_back((int64_t)string_to_price(n));
    }
    eosio_assert(vbets.size() == 11, "wrong size");

    // change format
    vector<int64_t> v(vbets);
    v[0] = vbets[1];  // (1)
    v[1] = vbets[6];  // (2)
    v[2] = vbets[0];  // (3)
    v[3] = vbets[4];  // (4)
    v[4] = vbets[9];  // (5)
    v[5] = vbets[5];  // (6)
    v[6] = vbets[10]; // (7)
    v[7] = vbets[2];  // (8)
    v[8] = vbets[3];  // (9)
    v[9] = vbets[7];  // (10)
    v[10] = vbets[8]; // (11)

    return v;
}

auto eoscrazytown::getBeton(const vector<int64_t> &v)
{
    string beton = "";
    for (auto n : v)
        beton += (n != 0) ? 'O' : 'n';

    return beton;
}

const int64_t eoscrazytown::getTotalBets(const vector<int64_t> &v)
{
    int64_t totalBets = 0;
    for (auto n : v)
        totalBets += n;

    return totalBets;
}

uint64_t merge_seed(const checksum256 &s1, const checksum256 &s2) {
    uint64_t hash = 0, x;
    for (int i = 0; i < 32; ++i) {
        hash ^= (s1.hash[i]) << ((i & 7) << 3);
      //  hash ^= (s1.hash[i] ^ s2.hash[31-i]) << ((i & 7) << 3);
    }
    return hash;
}

// Output
void eoscrazytown::reveal(const checksum256 &seed, const checksum256 &hash)
{ // hash for next round
    require_auth(_self);

    auto g = _global.get();

 //   assert_sha256((char *)&seed, sizeof(seed), (const checksum256 *)&g.hash);

    eosio_assert(! (g.hash == checksum256(hash)), "same hash");
    g.hash = hash;


 //   eosio_assert(players.begin() != players.end(), "must have at least one player");
    auto t = merge_seed(seed, seed);
    card dragon = t % 52;
    card tiger = t / 52 % 52;
    const rec_reveal _reveal{
        .dragon = dragon,
        .tiger = tiger,
        .server_hash = _global.get().hash,
        .client_seed = seed,
    };

    action( // give result to client
        permission_level{_self, N(active)},
        _self, N(receipt), _reveal)
        .send();

    auto result = getResult(_reveal.dragon, _reveal.tiger);

    string beton;
    string presult = "";
    int64_t bonus;
    const char o = 'O';
    for (const auto &p : players)
    {
        auto &bets = p.vbets;
        beton = getBeton(bets);

        bonus = 0;
        presult = "";
        // exp:
        // r 2.0: O X X X X X X X X X X // no space !
        // beton: O X X O X X O X O O O // no space !
        if (result[2] == o)
        { // (3) draw
            if (result[2] == beton[2])
                bonus += bets[2] + bets[2] * DRAW; // (3)
            bonus += bets[0] / 2;
            bonus += bets[1] / 2;
            /*
            if ( result[3] == beton[3] ) bonus += bets[3] + bets[3] * COLOR ; // (4)
            if ( result[4] == beton[4] ) bonus += bets[4] + bets[4] * COLOR ; // (5)

            if ( result[5] == beton[5] ) bonus += bets[5] + bets[5] * COLOR ; // (6)
            if ( result[6] == beton[6] ) bonus += bets[6] + bets[6] * COLOR ; // (7)
            */
        }
        else
        {
            if (result[0] == o)
            {
                if (result[0] == beton[0])
                {
                    bonus += bets[0] + bets[0] * SIDE; // (1)
                    presult += '1';
                }
            }
            else
            { // result[1] == o
                if (result[1] == beton[1])
                {
                    bonus += bets[1] + bets[1] * SIDE; // (2)
                    presult += '2';
                }
            }
        }
        
        if (result[3] == beton[3])
        {
            bonus += bets[3] + bets[3] * COLOR; // (4)
            presult += '4';
        }

        if (result[4] == beton[4])
        {
            bonus += bets[4] + bets[4] * COLOR; // (5)
            presult += '5';
        }

        if (result[5] == beton[5])
        {
            bonus += bets[5] + bets[5] * COLOR; // (6)
            presult += '6';
        }
        if (result[6] == beton[6])
        {
            bonus += bets[6] + bets[6] * COLOR; // (7)
            presult += '7';
        }

        if (result[7] == beton[7])
        {
            bonus += bets[7] + bets[7] * ODD; // (8)
                presult += '8';
        }
        if (result[8] == beton[8])
        {
            bonus += bets[8] + bets[8] * EVEN; // (9)
            presult += '9';
        }
        if (result[9] == beton[9])
        {
            bonus += bets[9] + bets[9] * ODD; // (10)
            presult += 'A';
        }
        if (result[10] == beton[10])
        {
            bonus += bets[10] + bets[10] * EVEN; // (11)
            presult += 'B';
        }        

        if(bonus != 0 && bonus<=2000000){    
            send_defer_action(
                permission_level{_self, N(active)},
                N(eosio.token), N(transfer),
                make_tuple(_self, p.account, asset(bonus, EOS_SYMBOL),
                        string("Winner Winner Chicken Dinner. " + presult)));            
        }
        auto _amountOfEos = getTotalBets(bets);
        auto _amountToMiner = _amountOfEos * 40;

        send_defer_action(
            permission_level{_self, N(active)},
            N(dacincubator), N(transfer),
            make_tuple(_self, p.account, asset(_amountToMiner, CTN_SYMBOL),
                string("for miner." + presult))
        );        
    }

    g.dragon = dragon;
    g.tiger = tiger;
    _global.set(g, _self);

    while (players.begin() != players.end())
    {
        players.erase(players.begin());
    }

    // init( hash ) ;
}


