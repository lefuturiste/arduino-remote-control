const express = require('express')
const app = express()
const path = require('path')
const serialport = require('serialport')

let comName = process.env.USB_COM_NAME

serialport.list(function (err, ports) {
  if (err !== null) {
    console.log('Error while getting the list of serialport')
    console.log(err)
  }
  comName = ports[0].comName


  const Arduino = serialport(comName, {
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

  let port = 3001;
  let host = "0.0.0.0";
  if (process.PORT !== undefined) {
    port = process.PORT
  }
  if (process.env.HOST !== undefined) {
    host = process.HOST
  }
  app.listen(port, host)
  console.log(`App listening on http://${host}:${port}`)

});
