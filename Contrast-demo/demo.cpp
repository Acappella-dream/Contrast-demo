#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;
using namespace std;

class demo : public eosio::contract {
    struct address{
        uint64_t account_name;
        string note;

        uint64_t primary_key() const { return account_name; }
		EOSLIB_SERIALIZE(address, (account_name)(note))
    };
  public:
    demo(account_name self) :contract(self) {}
	typedef eosio::multi_index< N(address), address > address_index;
	

      /// @abi action 
    using contract::contract;
    void insert( account_name _account, string _note) {
        address_index addresses(_self, _self); // code, scope
        addresses.emplace(_self, [&](auto& address) { //_self是支付这笔修改费用的帐号，即自己
            address.account_name = N(name{_account});
            address.note = _note;
        });
    }

    void find(account_name _account){
        address_index addresses(_self, _self); // code, scope
        auto itr = addresses.find(N(name{_account}));
        if(itr != addresses.end())
            print(itr->note);
    }
};

EOSIO_ABI( demo, (insert)(find) )
