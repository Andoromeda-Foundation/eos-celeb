import { eos } from './store'
import MockData from "./mock_celeb.json";

export async function getContractGlobal() {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'myeosgroupon',
    scope: 'myeosgroupon',
    limit: 50,
    table: 'global'
  })
  return rows[0]
}

export async function getCelebs() {
  return MockData
}

export async function getCelebsPrice(celebIds) {
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