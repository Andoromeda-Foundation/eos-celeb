#cleos wallet unlock -n www --password PW5JDQJvz73w73eNEtthCRhLn9gieFki5uiZu1JZdjwMftVA3f4cG

cleos wallet unlock --password PW5JaGpLtoM1vtD1WxiAC4RDsr82FRUczmKgocw1KJZqVahB4LZ1u
/usr/local/eosio/bin/eosiocpp -g eoscrazytown/eoscrazytown.abi  eoscrazytown/eoscrazytown.cpp
/usr/local/eosio/bin/eosiocpp -o eoscrazytown/eoscrazytown.wast eoscrazytown/eoscrazytown.cpp

cleos -u http://api.eosbeijing.one set contract crazytown.bp eoscrazytown -p crazytown.bp@active

#
#

#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "eosotcbackup", "crazytown.bp", "0.0100 CTN", "stake" ]' -p eosotcbackup@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "0.0100 EOS", "make_profit" ]' -p minakokojima@active
#cleos -u http://api.eosbeijing.one get table crazytown.bp crazytown.bp players

#cleos -u http://api-direct.eosasia.one push action crazytown.bp init '[123]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp test '[]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "crazytown.bp", "minakokojima", "1000000.0000 CTN", "" ]' -p crazytown.bp@active

#
#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "crazytown.bp", "thinksaturna", "1000000.0000 CTN", "Winner Winner Chicken Dinner" ]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "150.2802 EOS", "" ]' -p minakokojima@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "crazytown.bp", "fakemonk1234", "118.8000 EOS", "Winner Winner Chicken Dinner" ]' -p crazytown.bp@active
#158.4
#cleos -u http://api.eosbeijing.one push action crazytown.bp newbag '[ "minakokojima", "0.0100 EOS" ]' -p crazytown.bp@active minakokojima@active


#cleos -u http://api.eosbeijing.one push action crazytown.bp newbag '[ "crazytown.bp", "0.0100 EOS" ]' -p crazytown.bp@active crazytown.bp@active

#cleos -u http://api.eosbeijing.one set contract crazytown.bp eoscrazytown -p crazytown.bp@active

#cleos -u http://api.eosbeijing.one set contract crazytown.bp eoscrazytown -p crazytown.bp@active


#leos -u http://api.eosbeijing.one get table crazytown.bp eosotcbackup voter


#cleos -u http://api-direct.eosasia.one push action crazytown.bp unstake '[ "eosotcbackup"]' -p eosotcbackup@active




#cleos -u http://api.eosbeijing.one get table crazytown.bp crazytown.bp bag
#cleos -u http://api.eosbeijing.one get table crazytown.bp crazytown.bp bagsglobal

#cleos -u http://api-direct.eosasia.one push action crazytown.bp init '[]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp init '[]' -p crazytown.bp@active


#cleos -u http://api.eosbeijing.one push action crazytown.bp init '["0196d5b5d9ec1bc78ba927d2db2cb327d836f002601c77bd8c3f144a07ddc737"]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp reveal '["0196d5b5d9ec1bc78ba927d2db2cb327d836f002601c77bd8c3f144a07ddc737","0196d5b5d9ec1bc78ba927d2db2cb327d836f002601c77bd8c3f144a07ddc737"]' -p crazytown.bp@active
#cleos -u http://api-direct.eosasia.one push action crazytown.bp reveal '["7a2dee663b23200c63fe195f76c9cb0f255ff623e578134060dd3fbc9dfd06a2","7f86a67f22e04c1ff4a21ade119ec95f8e618b06588b160ee68035544eb40014"]' -p crazytown.bp@active
#cleos -u https://api.franceos.fr:443 push action crazytown.bp reveal '["7a2dee663b23200c63fe195f76c9cb0f255ff623e578134060dd3fbc9dfd06a2","7f86a67f22e04c1ff4a21ade119ec95f8e618b06588b160ee68035544eb40014"]' -p crazytown.bp@active


#cleos -u http://api-direct.eosasia.one push action crazytown.bp clear '[]' -p crazytown.bp@active
 
#https://api.franceos.fr:443

#cleos -u http://api-direct.eosasia.one push action crazytown.bp setwhitelist '["PXL", "dacincubator"]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp rmwhitelist '["PXL"]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "0.0010 EOS", "0.0010 PXL" ]' -p minakokojima@active

#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "eosotcbackup", "crazytown.bp", "0.0010 PXL", "0.0010 EOS" ]' -p eosotcbackup@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "0.0100 EOS", "0.0100 PUB" ]' -p minakokojima@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "crazytown.bp", "intimexixixi", "780.1653 EOS", "Congratulation!" ]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one get table crazytown.bp crazytown.bp global

#cleos -u http://api-direct.eosasia.one get table crazytown.bp crazytown.bp player

#cleos -u https://geo.eosasia.one get table crazytown.bp crazytown.bp player

#cleos -u http://api-direct.eosasia.one get table crazytown.bp crazytown.bp bags

#cleos -u http://api-direct.eosasia.one get table -l 65536 eosotcbackup eosio.token order


#cleos -u http://api-direct.eosasia.one get table dacincubator eosotcbackup accounts


# cleos -u https://api-kylin.eosasia.one push action eosio.token transfer '[ "minakokojima", "pomelodex111", "1.0000 EOS", "buy,happyeosslot,HPY,2.0000" ]' -p minakokojima@active
# /usr/local/eosio/bin/eosiocpp -g pomelo/pomelo.abi pomelo/pomelo.cpp
# cleos -u https://api-kylin.eosasia.one set contract pomelodex111 pomelo -p pomelodex111@active
# cleos -u https://api-kylin.eosasia.one system newaccount --stake-net '5.0000 EOS' --stake-cpu '1.0000 EOS' --buy-ram '20.0000 EOS' minakokojima pomelodex111 EOS5fY2dmpfXmzXN1DEJ6VfvhhCr55ZpE9MyTd9eX7Cw2EmzJcnFM EOS781pFN6TgUkuCDqmCdyxcp1cnJdtg3DYfajbAba6mvHvrFNuDy


# buy,happyeosslot,HPY,2.0000



#cleos wallet unlock --password PW5JaGpLtoM1vtD1WxiAC4RDsr82FRUczmKgocw1KJZqVahB4LZ1u
#
#/usr/local/eosio/bin/eosiocpp -g pomelo/pomelo.abi pomelo/pomelo.cpp


#
#cleos -u http://api-direct.eosasia.one set contract kyubeydex.bp pomelo -p kyubeydex.bp@active

#cleos -u http://api-direct.eosasia.one set contract crazytown.bp eoscrazytown -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp clear '' -p crazytown.bp@active

#
#cleos -u http://api-direct.eosasia.one push action crazytown.bp setslogan '[ "minakokojima", "0", "EOS Asia" ]' -p minakokojima@active


#cleos -u http://api-direct.eosasia.one push action kyubeydex.bp setwhitelist '["PXL", "dacincubator"]' -p kyubeydex.bp@active

#cleos -u http://api-direct.eosasia.one push action crazytown.bp rmwhitelist '["PXL"]' -p crazytown.bp@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "0.0010 EOS", "0.0010 PXL" ]' -p minakokojima@active

#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "eosotcbackup", "crazytown.bp", "0.0010 PXL", "0.0010 EOS" ]' -p eosotcbackup@active

#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "crazytown.bp", "0.0100 EOS", "0.0100 PUB" ]' -p minakokojima@active


#
#cleos -u http://api-direct.eosasia.one push action eosio.token transfer '[ "minakokojima", "kyubeydex.bp", "0.0100 EOS", "0.0100 KBY" ]' -p minakokojima@active
#
# 
#cleos -u http://api-direct.eosasia.one push action dacincubator transfer '[ "eosotcbackup", "kyubeydex.bp", "0.0050 PXL", "0.0050 EOS" ]' -p eosotcbackup@active kyubeydex.bp@active



#crazytown.bp PXL whitelist


#cleos -u http://api-direct.eosasia.one get table dacincubator dacincubator accounts

#cleos -u http://api-direct.eosasia.one get table kyubeydex.bp PXL buyorder

#


#cleos -u http://api-direct.eosasia.one get table crazytown.bp crazytown.bp buyorder

#cleos -u http://api-direct.eosasia.one get table tokendapppub PUB games


# cleos -u https://api-kylin.eosasia.one push action pomelodex111 test '[]' -p minakokojima@active


# cleos -u https://api-kylin.eosasia.one set contract pomelodex111 pomelo -p pomelodex111@active
# cleos -u https://api-kylin.eosasia.one push action eosio.token transfer '[ "minakokojima", "pomelodex111", "1.0000 EOS", "buy,happyeosslot,HPY,2.0000" ]' -p minakokojima@active
# cleos -u https://api-kylin.eosasia.one set contract pomelodex111 pomelo -p pomelodex111@active
# cleos -u https://api-kylin.eosasia.one push action eosio.token transfer '[ "minakokojima", "happyeosslot", "1.0000 EOS", "buy" ]' -p minakokojima@active

# cleos -u https://api-kylin.eosasia.one push action eosio.token transfer '[ "minakokojima", "pomelodex111", "1.0000 EOS", "buy,happyeosslot,HPY,2.0000" ]' -p minakokojima@active
# /usr/local/eosio/bin/eosiocpp -g pomelo/pomelo.abi pomelo/pomelo.cpp
# cleos -u https://api-kylin.eosasia.one set contract pomelodex111 pomelo -p pomelodex111@active
# cleos -u https://api-kylin.eosasia.one system newaccount --stake-net '5.0000 EOS' --stake-cpu '1.0000 EOS' --buy-ram '20.0000 EOS' minakokojima pomelodex111 EOS5fY2dmpfXmzXN1DEJ6VfvhhCr55ZpE9MyTd9eX7Cw2EmzJcnFM EOS781pFN6TgUkuCDqmCdyxcp1cnJdtg3DYfajbAba6mvHvrFNuDy


# buy,happyeosslot,HPY,2.0000
