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
    code: 'dacincubator',
    scope: 'dacincubator',
    limit: 50,
    table: 'market'
  })
  const { supply } = rows[0]
  // @Magic Number: 10000000000 = 10^10
  return (
    Number(supply.slice(0, -5)) / 10000000000).toFixed(4)
}

export async function getMarketData () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'dacincubator',
    scope: 'dacincubator',
    limit: 50,
    table: 'market'
  })
  const { supply, balance } = rows[0]
  const price = (Number(supply.slice(0, -5)) / 10000000000).toFixed(4)
  // @Magic Number: 10000000000 = 10^10
  return {
    price,
    supply,
    balance
  }
}
