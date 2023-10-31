const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  configureWebpack: {
    resolve: {
      fallback: {
        'path': require.resolve('path-browserify'),
        'crypto': require.resolve('crypto-browserify'),
        'fs': false,
        "stream": require.resolve('stream-browserify')
      }
    },
    module: {
      rules: [
        {
          test: /\.node$/,
          use: 'node-loader'
        }
      ]
    }
  }
})
