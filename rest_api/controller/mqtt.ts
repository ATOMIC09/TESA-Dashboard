import mqtt from "mqtt"

const user = process.env.NEXT_PUBLIC_MQTT_USERNAME
const password = process.env.NEXT_PUBLIC_MQTT_PASSWORD

const brokerurl = process.env.MQTT_URL as string



const client = mqtt.connect(brokerurl,{username:user,password})
    

export default client


