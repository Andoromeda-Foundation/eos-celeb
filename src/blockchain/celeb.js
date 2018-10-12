import { eos } from './store'
import MockData from './mock_celeb.json'

export async function getContractGlobal () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'myeosgroupon',
    scope: 'myeosgroupon',
    limit: 50,
    table: 'global'
  })
  return rows[0]
}

export async function getCelebBaseList () {
  return MockData.slice(0, 10)
}

export async function getCelebPriceList () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'crazytown.bp',
    scope: 'crazytown.bp',
    limit: 10,
    table: 'bag'
  })
  return rows
}

/*
export async function getCelebsPrice (celebIds) {
  debugger;
  const queryPool = celebIds.map(id => {
    return eos().getTableRows({
      json: 'true',
      code: 'myeosgroupon', // the contract
      scope: id, // 'scope' should be the id
      limit: 50,
      table: 'celeb' // change table name if needed
    })
  })
  return Promise.all(queryPool)
}
*/
