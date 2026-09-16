const express = require('express');
const router = express.Router();
const db = require('../config/db');
const path = require('path');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const isValidEmail = require('../middleware/valid_email'); // Importe la fonction


router.use(express.urlencoded({ extended: true }));
router.use(express.json());
router.use(express.static(path.join(__dirname, 'public')));

router.post('/', async (req, res) => {
    const { email, name, firstname, password } = req.body;

    if (!isValidEmail(email)) {
        return res.status(400).json({ msg: 'Invalid email format' });
    }
    try {
        const hashedPassword = await bcrypt.hash(req.body.password, 10);
        const query = 'INSERT INTO user (email, name, firstname, password) VALUES (?, ?, ?, ?)';
        db.query(query, [email, name, firstname, hashedPassword], (error, results) => {
            if (error) {
                console.log('Error:', error);
                return res.status(409).json({ msg: 'Account already exists' });
            }
            const token = jwt.sign({username: name, email: email }, process.env.SECRET, {});
            res.status(200).json({token: token});
        });
    } catch (error) {
        console.log('error');
        res.status(500).json({msg: 'An error occured'});
    }
})

router.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../public', 'register.html'));
})

module.exports = router;
