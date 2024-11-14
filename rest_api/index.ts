import express from 'express'
import bodyParser from 'body-parser'
import * as fs from 'fs';
import cors from 'cors'
import 'dotenv/config'
import { logger } from './config/logger';
import { validateAPIKey } from './controller/middleware';
import sound from "./controller/sound"
import sounds from "./controller/sounds"


const app = express()
const port = process.env.port
const folderpath = ["./static/sound"]

app.use(cors())
app.use('/static', express.static('static'))


app.get("/", (req: express.Request, res: express.Response) => {
    res.send(`hello world`)
})

app.get('/key',validateAPIKey, (req: express.Request, res: express.Response) => {
    res.send(`hello world with API KEY`)
})

app.use('/sound',sound)
app.use("/sounds",sounds)


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