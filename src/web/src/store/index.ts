import axios from 'axios'
import { createStore } from 'vuex'

interface AppInfo {
  appName: string
}

interface UserData {
  username: string
  email: string
  phone: string
}

interface StoreInterface {
  appInfo?: AppInfo
  userToken: string
  userData?: UserData
}

export default createStore<StoreInterface>({
  state() {
    return {
      appInfo: undefined,
      userToken: "",
      userData: undefined
    }
  },
  getters: {
  },
  mutations: {
    set_userData(state, data:UserData | undefined){
      state.userData = data
    },
    fetch_appinfo(state){
      const req = axios.get('/api/appinfo')
      req.then(res => {
        state.appInfo = res.data
      }).catch(err => {
        console.error(err)
      })
    }
  },
  actions: {
    set_userData(context){
      context.commit('set_userData')
    },
    fetch_appinfo(context){
      context.commit('fetch_appinfo')
    }
  },
  modules: {
  }
})
