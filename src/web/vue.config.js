const { defineConfig } = require('@vue/cli-service')
const AutoImport = require('unplugin-auto-import/webpack');
const Components = require('unplugin-vue-components/webpack');
const { ElementPlusResolver } = require('unplugin-vue-components/resolvers');

module.exports = defineConfig({
  publicPath: process.env.NODE_ENV === 'production'
    ? '/web/' // Production path prefix
    : '/',
  transpileDependencies: true,
  configureWebpack: {
    plugins: [
      AutoImport({
        imports: ["vue"],
        resolvers: [ElementPlusResolver()],
      }),
      Components({
        resolvers: [ElementPlusResolver()],
        dirs: ['src/components']
      }),
    ],
  }
})
