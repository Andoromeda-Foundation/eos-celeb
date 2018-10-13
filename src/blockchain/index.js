import { currentGetters, eos } from './store'

export function getBalancesByContract ({ tokenContract = 'eosio.token', accountName, symbol }) {
  return eos().getCurrencyBalance(tokenContract, accountName, symbol)
}

export function getMyBalancesByContract ({ tokenContract = 'eosio.token', symbol }) {
  const accountName = currentGetters().account.name
  return getBalancesByContract({ tokenContract, accountName, symbol })
}
