const mysql = require("mysql");

const conn = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "33dwr986b1",
    database: "Projeto_SelfOrder"
});

conn.connect(error => {
    if (error) throw error;
    console.log('Conectado com Sucesso.');
});

module.exports = conn;
