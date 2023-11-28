const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  devServer: {
    host: '0.0.0.0',
    // https:true,
    port: 8080,
    client: {
      webSocketURL: 'ws://0.0.0.0:8080/ws',
    },
    headers: {
      'Access-Control-Allow-Origin': '*',
    },
  },
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
