const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
    res.send('hello world !');
})

app.get('/name/:name', (req, res) => {
    const name = req.params.name;
    res.send(`Hello ${name}!!!`);
});

app.get('/date', (req, res) => {
    const curr_date = new Date();
    res.send(`${curr_date.getFullYear()}-${curr_date.getMonth()}-${curr_date.getDay()}`);
});

app.listen(port, () => {
    console.log(`Serveur en écoute sur http://localhost:${port}`);
});
