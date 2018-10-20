const express = require('express')
const app = express()
const path = require('path')
const serialport = require('serialport')

const Arduino = serialport('/dev/ttyUSB0', {
  baudRate: 9600
})

app.get('/', (req, res) => {
  return res.sendFile(path.resolve('./index.html'))
})

app.get('/red', (req, res) => {
  Arduino.write('1121')
  return res.json(true)
})

app.get('/green', (req, res) => {
  Arduino.write('1122')
  return res.json(true)
})

app.get('/blue', (req, res) => {
  Arduino.write('1123')
  return res.json(true)
})

app.get('/forward', (req, res) => {
  Arduino.write('1124')
  return res.json(true)
})

app.get('/backward', (req, res) => {
  Arduino.write('1125')
  return res.json(true)
})

app.get('/right', (req, res) => {
  Arduino.write('1126')
  return res.json(true)
})

app.get('/left', (req, res) => {
  Arduino.write('1127')
  return res.json(true)
})

app.get('/stop', (req, res) => {
  Arduino.write('1128')
  return res.json(true)
})

app.listen(3001, '0.0.0.0')
