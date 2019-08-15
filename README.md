# Quiet Hours by Team SOLUTI/ON (Feb 2-3, 2019)
[Vish Anand](https://www.vishanand.com), [Dean Ogle](https://github.com/DeanBrogle), [Noah Sediqe](https://github.com/NoahSediqe), & [JT Thrash](https://github.com/JT-Thrash)

[Presentation Given at the OSU MakeOHI/O Hackathon](https://drive.google.com/file/d/1Gth503BGLpS9QvUULUKfwbs327lDW-KX/view?usp=sharing)

Won **1st Place** for the Best Use of Voice Technology ([EdgeThingz sponsor challenge](https://hack.osu.edu/make/2019/#prizes-page))

### Objective
As Sophomores at Ohio State, the four of us were living in the Dorms and would often hear our RA's complain about excessive noise, so we decided to develop a system to automate the warning process---thereby making the RA's job easier. This system can also easily be adapted to other environments that would benefit from noise-level monitoring, such as hospitals and libraries.

### Technical Details
Our project had two major components:
* The Arduino-powered Listening Device
  * We wired a microphone to the Arduino's analog input ports so that it could monitor noise levels, we also wired it to four colored LED's that acted as status lights
  * The Arduino board we used had an ESP8266 Wireless module, so we pinged our server with the max noise levels from each 10-second interval every 10 seconds
  * Each Arduino device was assigned its own Device ID QR code so that we may scale our architecture to account for multiple Listening Devices in the future
  * The code was written using the Arduino IDE in a variant of C++
  * Source code is located at */Arduino/*
* The Node.js Backend
  * Ran off of a rented DigitalOcean server droplet in New York City during the Hackathon
  * The server code was written in Node.js, and it listened to pings from the Arduino at a specified endpoint
  * When the server detects excessive noise levels, it sends a message to a specified GroupMe group using GroupMe's [Bot API](https://dev.groupme.com) subject to appropriate cooldown periods
  * We also made a Bootstrap Configuration Panel that allows users to configure their Device ID, GroupMe Bot ID, custom messages to send for excessive noise, the cooldown period, and the acceptable volume threshold
  * Source code is located at */Server/*

## Pictures

**Front of device**
![Image](https://lh3.googleusercontent.com/m3K8Mjq-DKNwgCbJspnAKtMLqqukAMlKT5U7AvaIZceI2iPCEHrd14-nIbGSOLxMyYl3TU3EiVcBvxjdO7JzLlgk_E12y35wVepnvt08Yll1ze1N4Zk3Hm-b8--JKT9LRArs5tC3merb-ct_nMu3m_0-mU1sMrJibPUiIznbIh_mzwtGB8s-MesYfnal-04mxIZDasgc6SwJrm3jed15XYfE1y_IuIvqBP957Lo4Em3CSKX1dMmnyNBt0OuJWT8Tq9Sgbk1cGlxjYKb3kPoKhmY2wL5asfBsnoz6SG9QR6wyj2JbmVdkyB2JnVrDy9B7bI6GjbXvMO85naYd1yeitbCORiXyctozQnPQ7qTRqjDDQhR91pOmvtaWaNYciJVk9BJ9Z2_LB1Ji8KoCHszsuaFGokAIjzLPxUiRTi5xLyh3YwzycnxM6Amkc1l6xreWZkO_3vDo4G2_NmPNmmivldXIZcQOJgMCK1xMoD7k09UOX3jWrZr9GIlTQ0eXm2iRAWaZ_9yg9fCKlVa_816qSRHJ48KldFb01fHt6jI7t40IdKfGg8ICK9lokZH1HRj5-ec_cECrDrCn9ITgZn_bd8zKsqKJiwEMqggxQSAGMqg_0hvsS7KZN6sotMoRMv_qTmMCLER2eXk6jYghNYlS3-EOH3cph982=w1182-h886-no)

**Inside of device**
![Image](https://lh3.googleusercontent.com/s1EZ9IMpJ_W2eWvfVsd_xV8FcxKjStsf631_sRWYpI0wMO0h_ecK8D1lC112NSv2mYsZrzPW22zsMnV_foudGbSNciUc9SQA0M2um2fIE9Jkds3OAVVaOVz2_iCDZRjVK1VUfwTcNPmS9MweIurxlB0oqSemk_XVG2wltMqSnWXQE6wlKEHzbdYqiSJE_jMXb44uAWVGJcz6U2iG9YB4opGkTY8_BPHDhueb_gxhDJO7PNK0kvz57TsB9C8XbhqJL5Sho9qnCJf6xvrl3QnKFDpebarwnU5oUrU5xnhdZP-wX1KoLmwrRz5VVP8rdcGR9qZJf0Q_C1UY8GUUYhAuXvdUdYxq7Wktl-D4wMGQIvz92EQw81Jq_EzxbkXSAtYL0k2dGc4Qam43yPEB2HpYK84CuCarbpCbDYIkjTM9oTXXgyND3N9d58F4TeKRH6Z_kJX0oCVzh8FY0eYttpHx-0sq2xE56f-BBRksuokecprBaxFoZ8AeQiUZbqnvdau6x3IoWD-a86CN5AyytQNFxj5OrI6JFzYR6JUEK6lUQ8vQjqdiF_-Blng8nbuS1djFP-0mSv0er411PX6i3dvi3U92rtoJoagL5OdT1eIkxyb1K5c7bEiFDuwStlGLPFRg-qIwpyrhXtca5RxQ48F_qdOW9NOUUWbc=w1182-h886-no)

![Image](https://lh3.googleusercontent.com/V2WSAtNRPJW3MAfjudKns7WlNjoFwyLv3SwVqUOFQ_hCwtZmeWEq02YvctNkb58cCO-LfB1QGKSZVJ3Q6-S5pG61F8LO0IA-OkWZWSguxZ2gYVzNiDx8xQAtnvlYp0rb657SP1cmr3aclAwmpMsESA_YCtp8K1oAuuBzAplQI5nFv6-Tyo-sIsYh3xJMz2XYDym_acgR_HwFo4Jb7K6LYISeJGWHvpjksmsT3LT1gYrqp-OuZ48Z2yt-IFrvTxsBelT9QUX-I1uxLuPho-mauPN9jlXXE85DY1Qh1P2u_ODXKOQTdPUYssWZ0X1u-DzopLPmgr3z0YWf1F7svU7aJOYtj8UY-IQxZecYbjQPi12ihUyeR0hUQLMpCUBRZ8M1E-wCJCdYMoz7p6i_k-14A4RlrglZ_EVEFBKwx23NKI126cpX6wmeXX2rUayksvaz1eB0gQS9o12KjKQQOpTg9Q_HJAmwpzmNYnDninoZnyIxD_a8PsltjI5rrhjZDxc3dzCraGZVzMq3hcGrHAbfkBMKifXQ2VvlJrCIZhtCox2zorTKA9peMkiuCP3cLxhQw1gda7xz_yMDj0nj10CYNSw4v0aT9_Qj_fnZYX0cdV6LC0QSPj4alAj_cTlSDvLJAax6XyEXTzvd1YQ_5fjEjYBMdxB167BY=w665-h886-no)
