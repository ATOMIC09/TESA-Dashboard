import { MongoClient } from 'mongodb';
import 'dotenv/config'


const database_link : string = process.env.monngolink as string;
const database_name : string = process.env.MONGO_INITDB_DATABASE as string;

const client = new MongoClient(database_link);
const database = client.db(database_name);

export default database