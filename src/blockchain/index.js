import { currentGetters, eos } from './store'

export function getBalancesByContract ({ tokenContract = 'eosio.token', accountName, symbol }) {
  return eos().getCurrencyBalance(tokenContract, accountName, symbol)
}

export function getMyBalancesByContract ({ tokenContract = 'eosio.token', symbol }) {
  const accountName = currentGetters().account.name
  return getBalancesByContract({ tokenContract, accountName, symbol })
}

export async function getTokenPrice () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'crazytown.bp',
    scope: 'crazytown.bp',
    limit: 50,
    table: 'bag'
  })
console.log("getTokenPrice")
    console.log(rows)
  const { owner,price } = rows[0]
  // @Magic Number: 10000000000 = 10^10
  return (
    Number(price) / 10000000000).toFixed(4)
}

export async function getMarketData () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'crazytown.bp',
    scope: 'crazytown.bp',
    limit: 50,
    table: 'bag'
  })
    console.log("getMarketData")
    console.log(rows)
  const { owner, balance,price } = rows[0]
  // const price = (Number(supply.slice(0, -5)) / 10000000000).toFixed(4)
  // @Magic Number: 10000000000 = 10^10
  return {
    price,
    owner,
    balance
  }
}
