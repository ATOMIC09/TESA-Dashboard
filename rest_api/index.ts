import express from 'express'
import bodyParser from 'body-parser'
import * as fs from 'fs';
import cors from 'cors'
import 'dotenv/config'
import { logger } from './config/logger';
import { validateAPIKey } from './controller/middleware';
import sound from "./controller/sound"
import sounds from "./controller/sounds"
import mqtt from 'mqtt';
import client from './controller/mqtt';


const app = express()
const port = process.env.port
const folderpath = ["./static/sound","./static/model"]
const topics = ["model/ticker"]

client.on("connect",()=>{
    logger.info('connect to MQTT Broker')
    for (const topic of topics) {
        client.subscribe(topic,(error)=>{
            if(!error){
                client.publish(topic,`YAY im restapi with mqtt`)
                logger.info(`Subcribe to topic ${topic}`)
            }
            else{
                logger.error(`error subscribe ${topic} on : ${error}`)
            }
        })
      }
})



app.use(cors())
app.use('/static', express.static('static'))


app.get("/", (req: express.Request, res: express.Response) => {
    res.send(`hello world`)
})

app.get('/key', validateAPIKey, (req: express.Request, res: express.Response) => {
    res.send(`hello world with API KEY`)
})

app.use('/sound', sound)
app.use("/sounds", sounds)


for (const i of folderpath) {
    if (!fs.existsSync(i)) {
        fs.mkdirSync(i, { recursive: true });
        logger.info(`Folder ${i} created`);
    } else {
        logger.info(`Folder ${i} already exist`);
    }
}
app.listen(port, () => {
    logger.info(`sever listening on port ${port}`);
})