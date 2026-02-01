<template>
    <div></div>
</template>

<script lang="ts">
import router from '@/router';
import { defineComponent } from 'vue';

export default defineComponent({
    name: 'HomeView',
    mounted() {
        router.push("/login")
    },
});

</script>