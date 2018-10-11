// 这个文件和 store 打交道
import store from '../store'

// trick: 延迟求值，因为 webpack 会直接处理初始为 undefined 的 `store`， currentState 此处可以绕过
export const currentState = () => store.state
export const currentGetters = () => store.getters
export const eos = () => store.state.eos
