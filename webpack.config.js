const path = require('path');
var nodeModulesPath = path.resolve(__dirname, 'node_modules');

module.exports = {
  entry: './src/typescript/NJS.ts',
  mode: 'development',
  devtool: 'inline-source-map',
  target: 'web',
  module: {
    rules: [
      // ts-loader: convert typescript (es6) to javascript (es6),
      // babel-loader: converts javascript (es6) to javascript (es5)
      {
        test: /\.tsx?$/,
        use: ['babel-loader','ts-loader'],
        exclude: [/node_modules/,nodeModulesPath]
      },
      // babel-loader for pure javascript (es6) => javascript (es5)
      {
        test: /\.(jsx?)$/,
        use: ['babel'],
        exclude: [/node_modules/,nodeModulesPath]
      }
    ]
  },
  optimization: {
    minimize: false
},
  resolve: {
    extensions: [ '.tsx', '.ts', '.js' ],
  },
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'dist'),
  },
};