import mqtt from "mqtt"
import { logger } from "../config/logger";

const user = process.env.user
const password = process.env.password

const brokerurl = process.env.mqtturl as string
const topics = ['model/ticker'];


const client = mqtt.connect(brokerurl,{username:user,password})
    

export default client


