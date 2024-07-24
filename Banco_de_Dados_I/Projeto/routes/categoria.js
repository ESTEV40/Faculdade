const express = require('express');
const router = express.Router();
const conn = require('../Data/db');

// Rota POST para adicionar uma nova categoria
router.post('/', (req, res) => {
  const { Nome_Categoria } = req.body;

  const sql = 'INSERT INTO Categoria (Nome_Categoria) VALUES (?)';
  
  conn.query(sql, [Nome_Categoria], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao inserir categoria.");
    }

    res.status(201).send("Categoria inserida com sucesso.");
  });
});

// Rota POST para atualizar uma categoria
router.post('/update', (req, res) => {
  const { ID_Categoria, Nome_Categoria } = req.body;

  const sql = 'UPDATE Categoria SET Nome_Categoria = ? WHERE ID_Categoria = ?';
  
  conn.query(sql, [Nome_Categoria, ID_Categoria], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao atualizar categoria.");
    }

    res.status(200).send("Categoria atualizada com sucesso.");
  });
});

// Rota POST para deletar uma categoria
router.post('/delete', (req, res) => {
  const { ID_Categoria } = req.body;

  const sql = 'DELETE FROM Categoria WHERE ID_Categoria = ?';
  
  conn.query(sql, [ID_Categoria], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao deletar categoria.");
    }

    res.status(200).send("Categoria deletada com sucesso.");
  });
});

module.exports = router;
