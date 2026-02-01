<template>
  <el-form class="login">
    <h3>{{ appInfo?.appName ?? 'Verteilen2' }}</h3>
    <el-form-item label="Username">
      <el-input 
        v-model="username"></el-input>
    </el-form-item>
    <el-form-item label="Password">
      <el-input 
        v-model="password" 
        type="password"></el-input>
    </el-form-item>
    <el-form-item>
      <el-button type="primary" @click="submitForm()">
        Login
      </el-button>
      <el-button type="primary" @click="toRegister()">
        Register
      </el-button>
    </el-form-item>
  </el-form>
</template>

<script lang="ts">
import router from '@/router';
import store from '@/store'
import axios from 'axios';
import { defineComponent } from 'vue';

export default defineComponent({
  name: 'login-view',
  computed: {
    appInfo(){
      return store.state.appInfo
    }
  },
  methods: {
    submitForm(){
      if(this.username.length == 0){
        this.error = "Username cannot be empty"
      }
      if(this.password.length == 0){
        this.error = "Password cannot be empty"
      }
      const req = axios.post("/api/login", {
        username: this.username,
        password: this.password
      })

      req.then(res => {
        if(res.status == 200){
          console.log('login success')
          router.push('/project')
        }else{
          console.log('login failed')
        }
      }).catch(err => {
        console.error(err)
      })
    },
    toRegister(){
      router.push('/register')
    }
  },
  data(){
    return {
      username: "",
      password: "",
      error: "",
    }
  }
})
</script>

<style lang="scss" scoped>
.login {
  width: 50vw;
  margin-top: 20vh;
  margin-left: 23vw;
  padding: 2vh 2vw;
  border: 1px solid black;
  border-radius: 10px;
}
</style>