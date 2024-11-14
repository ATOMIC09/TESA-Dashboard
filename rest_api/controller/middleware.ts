import fs from 'fs'
import express from 'express';
import { logger } from '../config/logger';

let lines: string[];

try {
    const data = fs.readFileSync('api_key.txt', 'utf8');
    console.log(data);
    lines = data.split('\r\n')
    console.log('Lines:', lines);
} catch (err) {
    console.error('Error reading file:', err);
}

export const validateAPIKey = (req: express.Request, res: express.Response, next: express.NextFunction) => {
    const authHeader = req.headers.authorization as string;
    console.log(authHeader);
    if (!authHeader) {
        res.status(403).json({ error: 'No API Key provided' });
        return
    }
    const token = authHeader.split(' ').findLast(() => true);
    if (!token) {
        res.status(403).json({ error: 'Malformed API Key' });
        return
    }
    try {

        if (lines.includes(token)) {
            logger.info(`Access API Key`);
            next();
        }
        else {
            res.status(401).json({ message: 'Invalid API Key' });
        }
    } catch (err) {
        logger.error(`API Key Verification failed: ${err}`);
        res.status(401).json({ message: 'Invalid API Key' });
    }
}
