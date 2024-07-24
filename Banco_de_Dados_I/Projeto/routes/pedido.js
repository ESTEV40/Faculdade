const express = require('express');
const router = express.Router();
const conn = require('../Data/db');

// Rota POST para fazer um novo pedido
router.post('/', (req, res) => {
  const { ID_PessoaComanda, ID_Produto } = req.body;

  const sql = 'INSERT INTO Pedido (ID_PessoaComanda, ID_Produto, STATUS) VALUES (?, ?, 0)';
  
  conn.query(sql, [ID_PessoaComanda, ID_Produto], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao fazer pedido.");
    }

    res.status(201).send("Pedido realizado com sucesso.");
  });
});

// Rota POST para cancelar um pedido
router.post('/cancelar', (req, res) => {
  const { ID_PessoaComanda, ID_Produto } = req.body;

  const sql = 'DELETE FROM Pedido WHERE ID_PessoaComanda = ? AND ID_Produto = ?';
  
  conn.query(sql, [ID_PessoaComanda, ID_Produto], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao cancelar pedido.");
    }

    if (results.affectedRows > 0) {
      res.status(200).send("Pedido cancelado com sucesso.");
    } else {
      res.status(404).send("Pedido não encontrado.");
    }
  });
});

// Rota para acompanhar pedidos
router.get('/acompanhar', (req, res) => {
  const ID_PessoaComanda = req.query.ID_PessoaComanda; // Obtém o ID_PessoaComanda dos parâmetros de consulta

  if (!ID_PessoaComanda) {
    return res.status(404).send("ERRO");
  }

  const sql = `
    SELECT 
      p.ID_Pedido,
      pr.Nome_Produto as Produto, 
      pr.Descricao_Produto as Descricao, 
      (pr.Valor_Produto - pr.Desconto_Produto) as Subtotal
    FROM 
      Pedido p
    INNER JOIN 
      Produto pr ON p.ID_Produto = pr.ID_Produto
    WHERE 
      p.ID_PessoaComanda = ?`;

  conn.query(sql, [ID_PessoaComanda], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao acompanhar pedidos.");
    }
    res.json(results);
  });
});

// Rota para cancelar pedido
router.delete('/cancelar/:ID_Pedido', (req, res) => {
  const { ID_Pedido } = req.params;

  const sql = 'DELETE FROM Pedido WHERE ID_Pedido = ?';
  conn.query(sql, [ID_Pedido], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao cancelar pedido.");
    }

    if (results.affectedRows > 0) {
      res.status(200).send("Pedido cancelado com sucesso.");
    } else {
      res.status(404).send("Pedido não encontrado.");
    }
  });
});

// Rota POST para atualizar o status de um pedido
router.post('/update_status', (req, res) => {
  const { ID_Pedido, STATUS } = req.body;

  const sql = 'UPDATE Pedido SET STATUS = ? WHERE ID_Pedido = ?';
  
  conn.query(sql, [STATUS, ID_Pedido], (err, results) => {
    if (err) {
      console.log(err);
      return res.status(500).send("Erro ao atualizar status do pedido.");
    }

    res.status(200).send("Status do pedido atualizado com sucesso.");
  });
});

module.exports = router;
