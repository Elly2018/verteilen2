import axios from 'axios'
import Cookies from 'js-cookie'
import { createStore } from 'vuex'

interface AppInfo {
  appName: string
}

interface UserData {
  uid: string
  id: string
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
    set_userData(state){
      state.userToken = Cookies.get('userToken') ?? ''
      const req = axios.get('/api/userdata')
      req.then(res => {
        state.userData = res.data
      }).catch(err => {
        console.error(err)
      })
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
    },
  },
  modules: {
  }
})
