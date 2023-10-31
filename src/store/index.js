import Vue from 'vue'
import Vuex from 'vuex'
import createPersistedState from 'vuex-persistedstate'
Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    user: {},
    iscollapse: false,
    isadd:false
  },
  getters: {
  },
  mutations: {
    setuser(state, value) {
      state.user = value
    },
    clearuser(state) {
      state.user={}
    },
    changeiscollapse(state) {
      state.iscollapse = !state.iscollapse
    },
    changeisadd (state,value) {
      state.isadd = value
    },
  },
  actions: {
  },
  modules: {
  },
  plugins: [createPersistedState({
    paths:['user','iscollapse']
  })]
})
