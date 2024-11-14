import mqtt from "mqtt"

const user = process.env.user
const password = process.env.password

const brokerurl = process.env.mqtturl as string



const client = mqtt.connect(brokerurl,{username:user,password})
    

export default client


