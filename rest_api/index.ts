import express from 'express'
import bodyParser from 'body-parser'
import * as fs from 'fs';
import cors from 'cors'
import 'dotenv/config'
import { validateAPIKey } from './controller/middleware';
import sound from "./controller/sound"
import sounds from "./controller/sounds"
import client from './controller/mqtt';
import model from "./controller/model"


const app = express()
const port = process.env.port
const folderpath = ["./static/sound","./static/model"]
const topics = ["model/ticker","sound/ticker "]

client.on("connect",()=>{
    console.log
    ('connect to MQTT Broker')
    for (const topic of topics) {
        client.subscribe(topic,(error)=>{
            if(!error){
                client.publish(topic,`YAY im restapi with mqtt`)
                console.log(`Subcribe to topic ${topic}`)
            }
            else{
                console.log
                (`error subscribe ${topic} on : ${error}`)
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
app.use("/model",model)


for (const i of folderpath) {
    if (!fs.existsSync(i)) {
        fs.mkdirSync(i, { recursive: true });
        console.log(`Folder ${i} created`);
    } else {
        console.log(`Folder ${i} already exist`);
    }
}
app.listen(port, () => {
    console.log(`sever listening on port ${port}`);
})