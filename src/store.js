import Vue from 'vue'
import Vuex from 'vuex'
import Eos from 'eosjs'
import * as API from './blockchain/celeb';
import { getMyBalancesByContract } from './blockchain'
import { network } from './config'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    scatter: null,
    identity: null,
    eos: null,
    balance: {
      eos: '0.0000 EOS',
      kby: '0.0000 KBY'
    },
    celebBaseList: [],
    celebPriceList: {},
    dataIsLoading: true,
    globalInfo: null,
  },
  getters: {
    account: ({ scatter }) => {
      if (!scatter) { return null }
      const { identity } = scatter
      return identity ? identity.accounts.find(({ blockchain }) => blockchain === 'eos') : null
    }
  },
  mutations: {
    setScatter (state, scatter) {
      state.scatter = scatter
      state.eos = scatter.eos(network, Eos, {})
      state.identity = scatter.identity
    },
    setIdentity (state, identity) {
      state.identity = identity
    },
    setCelebBase (state, baseList) {
      state.celebBaseList = baseList
    },
    setCelebPrice (state, priceList) {
      let newMap = {}
      priceList.forEach(item => {
        newMap[item.id] = item
      })
      state.celebPriceList = newMap
    },
    setBalance (state, { symbol, balance }) {
      state.balance[symbol] = balance || `0.0000 ${symbol.toUpperCase()}`
    },
    setDataLoading (state, loading) {
      state.dataIsLoading = loading
    },
    setGlobal (state, globalInfo) {
      state.globalInfo = globalInfo
    },
  },
  actions: {
    initScatter ({ commit, dispatch }, scatter) {
      commit('setScatter', scatter)
      dispatch('updateGlobal')
      dispatch('updateCeleb')
    },
    async updateCeleb ({ commit }) {
      commit('setDataLoading', true)
      const celebBaseList = await API.getCelebBaseList()
      const celebPriceList = await API.getCelebPriceList()
      commit('setCelebBase', celebBaseList)
      commit('setCelebPrice', celebPriceList)
      commit('setDataLoading', false)
    },
    async updateGlobal ({ commit }) {
      const globalInfo = await API.getGlobal()
      commit('setGlobal', globalInfo)
    },
    updateBalance ({ commit }) {
      getMyBalancesByContract({ symbol: 'eos' })
        .then((price) => {
          commit('setBalance', { symbol: 'eos', balance: price[0] })
        })
      getMyBalancesByContract({ symbol: 'kby', tokenContract: 'dacincubator' })
        .then((price) => {
          commit('setBalance', { symbol: 'kby', balance: price[0] })
        })
    },
    setIdentity ({ commit, dispatch }, identity) {
      commit('setIdentity', identity)
      dispatch('updateBalance')
    }
  }
})
