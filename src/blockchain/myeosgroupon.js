import { eos } from './store'

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
export async function getCrowdSaleOrders () {
  const { rows } = await eos().getTableRows({
    json: 'true',
    code: 'myeosgroupon',
    scope: 'myeosgroupon',
    limit: 65535,
    table: 'order'
  })
  return rows
}
