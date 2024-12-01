import express from "express";
import multer from "multer";
import { validateAPIKey } from "./middleware";
import { randomUUID } from "crypto";
import path from 'path';
import { renameSync } from 'fs'
import database from "../config/db";
import client from "./mqtt";

const router = express.Router()


const upload = multer({
    storage: multer.diskStorage({
        destination(req, file, cb) { cb(null, './static/model') },
        filename(req, file, callback) { callback(null, file.originalname) },
    })
})


router.post("/", validateAPIKey, upload.single("file"), async (req: express.Request, res: express.Response) => {
    if (req.body instanceof Array) {
        res.status(401).send({
            error: "Invalid request"
        })
    }
    const { timeStamp } = req.body
    if (!(req.file && req.file.fieldname && req.file.originalname)) {
        res.status(401).send({
            error: "Invalid request"
        })
    }
    const sound = req.file as Express.Multer.File
    const uuid = randomUUID();
    const filenameWithExt = path.parse(sound.originalname)
    const filename = filenameWithExt.name
    const ext = filenameWithExt.ext
    const oldPath = `${sound.destination}/${sound.originalname}`
    const newPath = `${sound.destination}/${filename}_${uuid}${ext}`
    console.log(`Old path : ${oldPath}`);
    console.log(`New path : ${newPath}`);
    renameSync(oldPath, newPath)

    const modeldata = {
        timeStamp, filePath: newPath.slice(1)
    }
    const col = database.collection('model')
    try {
        const data = await col.insertOne(modeldata)
        res.status(201).send({ message: "OK", ids: data })
        client.publish("model/ticker",process.env.NEXT_PUBLIC_BACKENDSERVER+newPath.slice(1))
     }
    catch (error) {
        console.log(`${error}`);
        res.status(500).send({ error: `${error}` })
    }

    
})

export default router