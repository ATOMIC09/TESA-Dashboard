import express from 'express'
import database from '../config/db'
import { logger } from '../config/logger'
import { validateAPIKey } from './middleware'


const router = express.Router()

router.get("/",validateAPIKey,async (req : express.Request , res : express.Response)=>{
    const {deviceId = null} = req.query
    if (typeof deviceId !== 'string' && deviceId !== null ){
        res.status(400).send({
            error: "invalid request"
        })
    }
    let filter = {}
    if (deviceId != null){
        filter = {deviceId}
    }
    const col = database.collection("sound")
    try {
        const data = await col.find(filter).toArray()
        res.send(data)
    }
    catch (error){
        logger.error(`${error}`);
        res.status(500).send({ error: `${error}` })
    }
})

export default router


