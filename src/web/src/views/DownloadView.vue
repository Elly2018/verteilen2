<template>
    <div></div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';

export default defineComponent({
    name: 'HomeView',
    data() {
        return {
            userAgent: "",
            userOs: ""
        };
    },
    mounted() {
        console.log('userAgent; ', navigator.userAgent);

        this.userAgent = navigator.userAgent || '';
        this.userOs = navigator.platform || '';

        let osType = this.userOs.toLowerCase();

        if (osType.includes('win')) alert('win');
        else if (osType.includes('mac')) alert('mac');
        else if (osType.includes('ios')) alert('ios');
        else if (osType.includes('android')) alert('android');
        else if (osType.includes('linux')) alert('linux');
        else alert('unkown os');
    },
});
</script>