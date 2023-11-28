import Vue from "vue";
import Vuex from "vuex";
import createPersistedState from "vuex-persistedstate";
Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    user: {},
    iscollapse: false,
    isadd: false,
    islight: true,
    isaddpdf: false,
    pdflist: [],
    index: 0,
    page:1
  },
  getters: {},
  mutations: {
    setuser(state, value) {
      state.user = value;
    },
    clearuser(state) {
      state.user = {};
    },
    changeiscollapse(state) {
      state.iscollapse = !state.iscollapse;
    },
    changeisadd(state, value) {
      state.isadd = value;
    },
    changeislight(state, value) {
      state.islight = value;
    },
    setpdflist(state, value) {
      state.pdflist.push(value)
    },
    clearpdflist(state) {
      state.pdflist = [];
    },
    changeindex(state, value) {
      if (Object.prototype.hasOwnProperty.call(value, "access")) {
        console.log(value);
        state.pdflist[state.index].access = value.access;
      }
      if (
        state.index + value.value !== -1 &&
        state.index + value.value !== state.pdflist.length
      ) {
        state.index += value.value;
        console.log(state.pdflist[state.index]);
      }
    },
    clearisaddpdf(state) {
      state.isaddpdf = false
      state.pdflist = []
      console.log("clear");
    }
  },
  actions: {},
  modules: {},
  plugins: [
    createPersistedState({
      paths: ["user", "iscollapse"],
    }),
  ],
});
