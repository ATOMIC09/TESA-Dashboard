import express from 'express'
import bodyParser from 'body-parser'
import * as fs from 'fs';
import 'dotenv/config'
import { logger } from './config/logger';
import { validateAPIKey } from './controller/middleware';


const app = express()
const port = process.env.port
const folderpath = ["./static/sound"]


app.get("/", (req: express.Request, res: express.Response) => {
    res.send(`hello world`)
})

app.get('/key',validateAPIKey, (req: express.Request, res: express.Response) => {
    res.send(`hello world with API KEY`)
})


for (const i of folderpath) {
    if (!fs.existsSync(i)) {
        fs.mkdirSync(i, { recursive: true });
        logger.info(`Folder ${i} created`);
    } else {
        logger.info(`Folder ${i} already exist`);
    }
}
app.listen(port, () => {
    console.log(`sever listening on port ${port}`);
})