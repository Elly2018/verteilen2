<template>
    <div>

    </div>
</template>

<script lang="ts">
import router from '@/router';
import axios from 'axios';
import { defineComponent } from 'vue';

export default defineComponent({
    name: 'HomeView',
    mounted() {
        axios.get(`${window.location.origin}/api/isinit`).then(res => {
            if(res.status == 200){
                const data = res.data
                if(Object.keys(data).includes("status")){
                    if(data.status){
                        router.push("/login")
                        return
                    }
                }
            }
            router.push("/setup")
        }).catch(err => {
            console.error(err)
            router.push("/setup")
        })
    },
});

</script>